using System;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.Text;



namespace WpfApp1
{
    public class Program
    {
        NetworkStream clientStream;
        public string _username = "";
        public const string IP = "127.0.0.1";
        public const int PORT = 8821;
        public Program()
        {
            ClientMain();
        }
        public string[] sendAndDecodeArrMessage(string msg)
        {
            byte[] res = sendAndReciveMessage(msg);
            bool flag = true;
            bool flag2 = true;
            bool flag3 = true;
            int i = 4;
            int strIndex = 0;
            string currStr = "";
            //"P000{\nlength:4\nNames[\n\"Elay\":1\n\"Nitay\":2\n\"Raz\":3\n\"Dana\":4\n]\n}"
            string[] arr = new string[0];
            while (Convert.ToChar(res[i]).ToString() != "]")
            {
                string currDataChar = Convert.ToChar(res[i]).ToString();
                if (currDataChar == ":" && flag)
                {
                    flag = false;
                    int length = Int32.Parse(Convert.ToChar(res[i + 1]).ToString());
                    if (length == 0)
                        return arr;
                    arr= new string[length];
                }
                else if (currDataChar == "[")
                {
                    flag3 = false;
                    i++;
                }
                else if (currDataChar == "\n" && flag2)
                    flag2 = false;
                else if (currDataChar == "\n" && !flag3)
                {
                    arr[strIndex] = currStr;
                    currStr = "";
                    strIndex++;
                }
                else if (!flag3 && currDataChar != "\"")
                    currStr += currDataChar;
                i++;
            }
            return arr;
        }
        public bool login(string username, string password)
        {
            this._username = username;
            string msg = "I" + "\0" + "\0" + (char)(30 + username.Length + password.Length) + (char)(username.Length) + (char)(password.Length) + " {\nusername:\"" + username + "\"\npassword:\"" + password + "\"\n}";
            byte[] res = sendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                return true;
            else
                return false;
        }

        public void signup()
        {
            Console.WriteLine("Enter Username");
            _username= Console.ReadLine();
            Console.WriteLine("Enter Password");
            string password = Console.ReadLine();
            Console.WriteLine("Enter Email");
            string email = Console.ReadLine();
            string msg = "U" + "\0" + "\0" + (char)(40 + _username.Length + password.Length + email.Length) + (char)(_username.Length) + (char)(password.Length) + (char)(email.Length) + " {\nusername:\"" + _username + "\"\npassword:\"" + password + "\"\nemail:\"" + email + "\"\n}";
            byte[] res = sendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                Console.WriteLine("Signup Succesfull");
            else
                Console.WriteLine("Failed To Sign Up");
        }

        public void logout(NetworkStream clientStream)
        {
            string msg = "O" + "\0" + "\0" +"\0";
            byte[] res = sendAndReciveMessage(msg);
            Console.WriteLine("Logged Out Succesfully");
        }

        public void getRooms()
        {
            string msg = "G" + "\0" + "\0" + "\0";
            string[] roomsArr=sendAndDecodeArrMessage(msg);
            if (roomsArr.Length == 0)
                Console.WriteLine("No Rooms Available");
            else
            {
                for (int p = 0; p < roomsArr.Length; p++)
                {
                    string name = roomsArr[p].Substring(0, roomsArr[p].Length - 2);
                    int id = System.Convert.ToInt32(roomsArr[p].Substring(roomsArr[p].Length - 1, 1)[0]);
                    Console.WriteLine("Name: " + name + " ID: " + id);
                }
            }
        }

        public void joinRoom()
        {
            Console.WriteLine("Enter Room ID");
            string roomID = Console.ReadLine();
            string msg = "J" + "\0" + "\0" + (char)1+roomID;
            byte[] res = sendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                Console.WriteLine("Joined Succesfully");
            else
                Console.WriteLine("Failed To Join");
        
        }

        public void getPlayersInRoom()
        {
            Console.WriteLine("Enter Room ID");
            string roomID = Console.ReadLine();
            string msg = "P" + "\0" + "\0" + (char)1 + roomID;
            string[] playersArr = sendAndDecodeArrMessage(msg);
            if (playersArr.Length == 0)
                Console.WriteLine("No Rooms Available");
            else
            {
                for (int p = 0; p < playersArr.Length; p++)
                {
                    string name = playersArr[p];
                    Console.WriteLine("Name: " + name.Substring(0, playersArr[p].Length));
                }
            }
        }

        public void getHighScores()//
        {
            string msg = "H" + "\0" + "\0" + "\0";
            string[] highScoresArr = sendAndDecodeArrMessage(msg);
            for (int i = 0; i < highScoresArr.Length; i++)
            {
                bool flag = true;
                int j = 0;
                for (j = 0; j < highScoresArr[i].Length && flag; j++)
                {
                    if (highScoresArr[i][j] == ':')
                    {
                        flag = false;
                    }
                }

                string name = highScoresArr[i].Substring(0, j - 1);
                string score = highScoresArr[i].Substring(j, highScoresArr[i].Length - j);
                Console.WriteLine(name + ": " + score);
            }
        }

        public void createRoom()
        {
            Console.WriteLine("Enter Room Name");
            string roomName = Console.ReadLine();
            Console.WriteLine("Enter Max Users");
            string maxUsers = Console.ReadLine();
            Console.WriteLine("Enter Questions Count");
            string questionsCount = Console.ReadLine();
            Console.WriteLine("Enter Answer Time");
            string answerTime = Console.ReadLine();
            string msg = "P" + "\0" + "\0" + (char)(58+roomName.Length+maxUsers.Length+questionsCount.Length+answerTime.Length) + "{RoomName:\"" + roomName + "\"\nMaxUsers:\"" + maxUsers+ "\"\nQuestionsCount:\"" + questionsCount+ "\"\nAnswerTime:\"" + answerTime+ "\"\n}";
            byte[] res = sendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                Console.WriteLine("Room Created Succesfully");
            else
                Console.WriteLine("Failed To Create Room");
        }

        public void exit()
        {
            string msg = "X" + "\0" + "\0"+ "\0";
            byte[] res = sendAndReciveMessage(msg);
            Console.WriteLine("Goodbye");
        }

        public byte[] sendAndReciveMessage(string s)
        {
            Console.WriteLine("Client Says: " + s);
            byte[] buffer = new ASCIIEncoding().GetBytes(s);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            int len = 4;
            buffer = new byte[len];
            int bytesRead = clientStream.Read(buffer, 0, len);

            len = buffer[1] << 16 | buffer[2] << 8 | buffer[3];
            buffer = new byte[len];
            bytesRead = clientStream.Read(buffer, 0, len);
            return buffer;
        }

        public void ClientMain()
        {
            try
            {
                TcpClient client = new TcpClient();
                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(IP), PORT);
                client.Connect(serverEndPoint);
                clientStream = client.GetStream();
            }
            catch (Exception e)
            {
                NoServerRuning er = new NoServerRuning();
                er.Show();
                return;
            }
            while (true)
            {
                Menu m = new Menu(this);
                m.Show();
            }
        }
    }
}