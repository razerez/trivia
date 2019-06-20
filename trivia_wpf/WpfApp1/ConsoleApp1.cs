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
        TcpClient client;
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

        public bool signup(string password, string email)
        {
            string msg = "U" + "\0" + "\0" + (char)(40 + _username.Length + password.Length + email.Length) + (char)(_username.Length) + (char)(password.Length) + (char)(email.Length) + " {\nusername:\"" + _username + "\"\npassword:\"" + password + "\"\nemail:\"" + email + "\"\n}";
            byte[] res = sendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                return true;
            else
                return false;
        }

        public void logout()
        {
            string msg = "O" + "\0" + "\0" +14+"\0" + " {\nusername:\"";
            byte[] res = sendAndReciveMessage(msg);
        }

        public string[] getRooms()
        {
            string msg = "G" + "\0" + "\0" + "\0";
            string[] roomsArr=sendAndDecodeArrMessage(msg);
            return roomsArr;
        }

        public bool joinRoom(int roomID)
        {
            string msg = "J" + "\0" + "\0" + (char)1+roomID;
            byte[] res = sendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                return true;
            else
                return false;
        
        }

        public string[] getPlayersInRoom(int roomID)
        {
            string msg = "P" + "\0" + "\0" + (char)1 + roomID;
            string[] playersArr = sendAndDecodeArrMessage(msg);
            return playersArr;
        }

<<<<<<< trivia_wpf/WpfApp1/ConsoleApp1.cs
        public void getHighScores()
=======
        public string[] getHighScores()//
>>>>>>> trivia_wpf/WpfApp1/ConsoleApp1.cs
        {
            string msg = "H" + "\0" + "\0" + "\0";
            string[] highScoresArr = sendAndDecodeArrMessage(msg);
            return highScoresArr;
        }

        public bool createRoom(string roomName, string maxUsers, string questionsCount, string answerTime)
        {
<<<<<<< trivia_wpf/WpfApp1/ConsoleApp1.cs
            Console.WriteLine("Enter Room Name");
            string roomName = Console.ReadLine();
            Console.WriteLine("Enter Max Users");
            string maxUsers = Console.ReadLine();
            Console.WriteLine("Enter Questions Count");
            string questionsCount = Console.ReadLine();
            Console.WriteLine("Enter Answer Time");
            string answerTime = Console.ReadLine();
            string msg = "P" + "\0" + "\0" + (char)(59+roomName.Length+maxUsers.Length+questionsCount.Length+answerTime.Length) + " {RoomName:\"" + roomName + "\"\nMaxUsers:\"" + maxUsers+ "\"\nQuestionsCount:\"" + questionsCount+ "\"\nAnswerTime:\"" + answerTime+ "\"\n}";
=======
            string msg = "P" + "\0" + "\0" + (char)(58+roomName.Length+maxUsers.Length+questionsCount.Length+answerTime.Length) + "{RoomName:\"" + roomName + "\"\nMaxUsers:\"" + maxUsers+ "\"\nQuestionsCount:\"" + questionsCount+ "\"\nAnswerTime:\"" + answerTime+ "\"\n}";
>>>>>>> trivia_wpf/WpfApp1/ConsoleApp1.cs
            byte[] res = sendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                return true;
            else
                return false;
        }

        public void exit()
        {
            string msg = "X" + "\0" + "\0" + 14 + "\0" + " {\nusername:\"";
            byte[] res = sendAndReciveMessage(msg);
        }

        public byte[] sendAndReciveMessage(string s)
        {
            Console.WriteLine("Client Says: " + s);
            byte[] buffer = new ASCIIEncoding().GetBytes(s);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            int len = client.ReceiveBufferSize;
            buffer = new byte[len];
            int bytesRead = clientStream.Read(buffer, 0, len);


            
            return buffer;
        }

        public void ClientMain()
        {
            try
            {
                client = new TcpClient();
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
            Menu m = new Menu(this, false);
            m.Show();
        }
    }
}