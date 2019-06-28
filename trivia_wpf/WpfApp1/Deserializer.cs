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
        public const int DATA_LENGTH_SEGMENT = 3;

        public const int STATUS_SIZE_SEGMENT = 1;
        public const int HAS_STARTED_SIZE_SEGMENT = 1;
        public const int QUESTION_COUNT_SIZE_SEGMENT = 1;
        public const int ANSWER_TIME_SIZE_SEGMENT = 1;
        public const int LENGTH_SIZE_SEGMENT = 1;

        public int _dataLocationSign = 1;

        public Room DeserializeJoinRoomRequest(byte[] buffer)
        {
            string status = AnalyzeJson(buffer, "Status:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT, STATUS_SIZE_SEGMENT);
            string hasStarted = AnalyzeJson(buffer, "HasStarted:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT, HAS_STARTED_SIZE_SEGMENT);
            string questionCount = AnalyzeJson(buffer, "QuestionCount:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT + HAS_STARTED_SIZE_SEGMENT, QUESTION_COUNT_SIZE_SEGMENT);
            string answerTime = AnalyzeJson(buffer, "AnswerTimeout:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT + HAS_STARTED_SIZE_SEGMENT + QUESTION_COUNT_SIZE_SEGMENT, ANSWER_TIME_SIZE_SEGMENT);
            string length = AnalyzeJson(buffer, "length:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT + HAS_STARTED_SIZE_SEGMENT + QUESTION_COUNT_SIZE_SEGMENT + ANSWER_TIME_SIZE_SEGMENT, LENGTH_SIZE_SEGMENT);
            Room room = new Room(Int32.Parse(status), Int32.Parse(hasStarted), questionCount.ToString(), answerTime.ToString(), Int32.Parse(length));
            FillNames(room, buffer, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT + HAS_STARTED_SIZE_SEGMENT + QUESTION_COUNT_SIZE_SEGMENT + ANSWER_TIME_SIZE_SEGMENT + LENGTH_SIZE_SEGMENT);
            return room;
        }

        public void FillNames(Room room, byte[] buffer, int startFrom)
        {
            bool stay = true;
            int j = 0;
            for (int i = startFrom; i < buffer.Length && stay; i++)
            {
                if(buffer[i] == '"')
                {
                    int end = FindStrIndex("\"", buffer, i);
                    string name = GetBytes(i, end - i, buffer);
                    room._names[j] = name;
                    j++;
                    i = end;

                }
            }
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
            str = str.ToLower();//make the str lowercase -> not case sensetive
            string bufferStr = System.Text.Encoding.UTF8.GetString(buffer);//crate string from vector
            bufferStr = bufferStr.Substring(skipTo - 1, bufferStr.Length - (skipTo - 1));//cut all until startPoint
            bufferStr = bufferStr.ToLower();//make the str lowercase -> not case sensetive
            int index = bufferStr.IndexOf(str);
            if (index == -1)//string not found
            {
                return -1;
            }
            return index + skipTo; //return index of str in buffer
        }
    }
}
