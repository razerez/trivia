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
        
        public bool SendAndReciveBoolMessage(string msg)
        {
            byte[] res = SendAndReciveMessage(msg);
            if (res[4] == (char)(1))
                return true;
            else
                return false;
        }
        public string[] SendAndDecodeArrMessage(string msg)
        {
            byte[] res = SendAndReciveMessage(msg);
            bool flag = true;
            bool flag2 = true;
            bool flag3 = true;
            int i = 5;
            int length;
            int strIndex = 0;
            string currStr = "";
            //"C000{\nlength:4\nNames[\n\"Elay\":1\n\"Nitay\":2\n\"Raz\":3\n\"Dana\":4\n]\n}"
            /*
             C000{
             length:1
             Names[
             "Elay":2
             ]

             */
            string[] arr = new string[0];
            while (Convert.ToChar(res[i]).ToString() != "]")
            {
                string currDataChar = Convert.ToChar(res[i]).ToString();
                if (currDataChar == ":" && flag)
                {
                    flag = false;

                    string lengthString = "";
                    bool loopFlag = true;
                    for (int k = 1; k != res.Length - i - 1&&loopFlag; k++)
                    {
                        if (res[i + k] != '\n')
                            lengthString += ((char)res[i + k]).ToString();
                        else
                            loopFlag = false;
                    }
                    length = Int32.Parse(lengthString);
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
        public bool Login(string username, string password)
        {
            this._username = username;
            string msg = "I" + "\0" + "\0" + (char)(30 + username.Length + password.Length) + (char)(username.Length) + (char)(password.Length) + " {\nusername:\"" + username + "\"\npassword:\"" + password + "\"\n}";
            return SendAndReciveBoolMessage(msg);
        }

        public bool Signup(string password, string email)
        {
            string msg = "U" + "\0" + "\0" + (char)(40 + _username.Length + password.Length + email.Length) + (char)(_username.Length) + (char)(password.Length) + (char)(email.Length) + " {\nusername:\"" + _username + "\"\npassword:\"" + password + "\"\nemail:\"" + email + "\"\n}";
            return SendAndReciveBoolMessage(msg);
        }

        public bool Logout()
        {
            string msg = "O" + "\0" + "\0" +(char)(14)+"\0" + " {\nusername:\"";
            return SendAndReciveBoolMessage(msg);
        }

        public string[] GetRooms()////////////////////////////////////needs to update response
        {
            string msg = "G" + "\0" + "\0" + "\0";
            string[] roomsArr=SendAndDecodeArrMessage(msg);
            return roomsArr;
        }

        public bool CloseRoom()
        {
            string msg = "D" + "\0" + "\0" + "\0";
            return SendAndReciveBoolMessage(msg);
        }

        public bool StartGame()
        {
            string msg = "S" + "\0" + "\0" + "\0";
            return SendAndReciveBoolMessage(msg);
        }

        public Room GetRoomState()
        {
            string msg = "R" + "\0" + "\0" + "\0";
            byte[] res = SendAndReciveMessage(msg);
            Room room = new Deserializer().DeserializeJoinRoomResponse(res);
            return room;
        }

        public bool LeaveRoom()
        {
            string msg = "L" + "\0" + "\0" + "\0";
            return SendAndReciveBoolMessage(msg);
        }

        public bool JoinRoom(int roomID)
        {
            string msg = "J" + "\0" + "\0" + (char)(1) + roomID;
            return SendAndReciveBoolMessage(msg);
        }

        public string[] GetPlayersInRoom(int roomID)/////////////////////////////////////needs to update response
        {
            string msg = "P" + "\0" + "\0" + (char)(1) + roomID;
            string[] playersArr = SendAndDecodeArrMessage(msg);
            return playersArr;
        }
        public Status myStatus()/////////////////////////////////////needs to update response
        {
            string msg = "M" + "\0" + "\0" + "\0";
            byte[] s = SendAndReciveMessage(msg);
            Status stat = new Deserializer().DeserializeStatusResponse(s);
            return stat;
        }
        public string[] GetHighScores()////////////////////////////////////needs to update response
        {
            string msg = "H" + "\0" + "\0" + "\0";
            string[] highScoresArr = SendAndDecodeArrMessage(msg);
            return highScoresArr;
        }

        public bool CreateRoom(string roomName, string maxUsers, string questionsCount, string answerTime)
        {
            string msg = "C" + "\0" + "\0" + (char)(64+roomName.Length+maxUsers.Length+questionsCount.Length+answerTime.Length)+ (char)(roomName.Length)+ (char)(maxUsers.Length)+ (char)(questionsCount.Length)+(char)(answerTime.Length) + " {\nRoomName:\"" + roomName + "\"\nMaxUsers:\"" + maxUsers+ "\"\nQuestionsCount:\"" + questionsCount+ "\"\nAnswerTime:\"" + answerTime+ "\"\n}";
            return SendAndReciveBoolMessage(msg);
        }

        public void Exit()
        {
            string msg = "X" + "\0" + "\0" + (char)(14) + "\0" + " {\nusername:\"";
            byte[] res = SendAndReciveMessage(msg);
        }

        public byte[] SendAndReciveMessage(string s)
        {
            byte[] final;
            Console.WriteLine("Client Says: " + s);
            byte[] buffer = new ASCIIEncoding().GetBytes(s);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            if (s[0] !='X')
            {
                int len = 4;
                buffer = new byte[len];
                int bytesRead = clientStream.Read(buffer, 0, len);
                len = buffer[1] << 16 | buffer[2] << 8 | buffer[3];
                byte[] buffer1 = new byte[len];
                bytesRead = clientStream.Read(buffer1, 0, len);
                final = new byte[buffer.Length + buffer1.Length];
                System.Buffer.BlockCopy(buffer, 0, final, 0, buffer.Length);
                System.Buffer.BlockCopy(buffer1, 0, final, buffer.Length, buffer1.Length);
            }
            else
            {
                final = new byte[0];
            }
            return final;
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
        ~Program()
        {
            try { Exit(); }
            catch (Exception e){ return;
            }
        }

    }
}