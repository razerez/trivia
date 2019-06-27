using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace WpfApp1
{
    class Deserializer
    {
        public const int CODE_SEGMENT = 1;
        public const int LENGTH_SEGMENT = 1;

        public const int ROOM_NAME_SIZE_SEGMENT = 1;
        public const int MAX_USERS_SIZE_SEGMENT = 1;
        public const int QUESTION_COUNT_SIZE_SEGMENT = 1;
        public const int ANSWER_TIME_SIZE_SEGMENT = 1;

        public int _dataLocationSign;

        public Room DeserializeJoinRoomRequest(byte[] buffer)
        {
            string questionCount = AnalyzeJson(buffer, "QuestionsCount:", _dataLocationSign, CODE_SEGMENT + LENGTH_SEGMENT + ROOM_NAME_SIZE_SEGMENT + MAX_USERS_SIZE_SEGMENT, QUESTION_COUNT_SIZE_SEGMENT);
            string answerTime = AnalyzeJson(buffer, "AnswerTime:", _dataLocationSign, CODE_SEGMENT + LENGTH_SEGMENT + ROOM_NAME_SIZE_SEGMENT + MAX_USERS_SIZE_SEGMENT + QUESTION_COUNT_SIZE_SEGMENT, ANSWER_TIME_SIZE_SEGMENT);
            return new Room(questionCount.ToString(), answerTime.ToString());
        }

        public string AnalyzeJson(byte[] buffer, string subject, int dataLocation, int sizeLocation, int sizeLength)
        //input: buffer, keyWord to search in json, locationOfTheKeyWord, location of the size of the segment, the length of this size
        //returns analyzed string from json and insert next dataLocation into this->_dataLocation
        {
            int size = buffer[sizeLocation];
            int keyIndex = FindStrIndex(subject, buffer, dataLocation);
            int strIndex = FindStrIndex("\"", buffer, keyIndex);

            string str = GetBytes(strIndex, size, buffer);
            _dataLocationSign = strIndex + size;
            return str;
        }

        string GetBytes(int skipTo, int dataSize, byte[] buffer)
        {
            string ret = "";
            for (int i = skipTo; i < dataSize + skipTo; i++)
            {
                ret += buffer[i];
            }
            return ret;
        }

        int FindStrIndex(string str, byte[] buffer, int skipTo)
        {
            str.ToLower();//make the str lowercase -> not case sensetive
            string bufferStr = buffer.ToString();//crate string from vector
            bufferStr = bufferStr.Substring(skipTo - 1, bufferStr.Length);//cut all until startPoint
            bufferStr.ToLower();//make the str lowercase -> not case sensetive
            int index = bufferStr.IndexOf(str);
            if (index == -1)//string not found
            {
                return -1;
            }
            return index + skipTo; //return index of str in buffer
        }
    }
}
