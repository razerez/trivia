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


        public const int NUMBER_OF_GAMES_SIZE_SEGMENT = 1;
        public const int NUM_RIGHT_SIZE_SEGMENT = 1;
        public const int NUM_WRONG_SIZE_SEGMENT = 1;
        public const int AVG_TIME_PER_ANSWER_SIZE_SEGMENT = 1;

        public const int QUESTION_SIZE_SEGMENT = 1;

        public const int CORRECT_ANSWER_SIZE_SEGMENT = 1;

        public int _dataLocationSign = 1;

        public Room DeserializeJoinRoomResponse(byte[] buffer)
        {
            _dataLocationSign = 1;
            string status = AnalyzeJson(buffer, "Status:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT, STATUS_SIZE_SEGMENT);
            string hasStarted = AnalyzeJson(buffer, "HasStarted:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT, HAS_STARTED_SIZE_SEGMENT);
            string questionCount = AnalyzeJson(buffer, "QuestionCount:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT + HAS_STARTED_SIZE_SEGMENT, QUESTION_COUNT_SIZE_SEGMENT);
            string answerTime = AnalyzeJson(buffer, "AnswerTimeout:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT + HAS_STARTED_SIZE_SEGMENT + QUESTION_COUNT_SIZE_SEGMENT, ANSWER_TIME_SIZE_SEGMENT);
            string length = AnalyzeJson(buffer, "length:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT + HAS_STARTED_SIZE_SEGMENT + QUESTION_COUNT_SIZE_SEGMENT + ANSWER_TIME_SIZE_SEGMENT, LENGTH_SIZE_SEGMENT);
            Room room = new Room(status, hasStarted, questionCount, answerTime, Int32.Parse(length));
            FillNames(room, buffer, FindStrIndex("[", buffer, 1));
            return room;
        }

        public Status DeserializeStatusResponse(byte[] buffer)
        {
            _dataLocationSign = 1;
            string numberOfGames = AnalyzeJson(buffer, "NumberOfGames:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT, NUMBER_OF_GAMES_SIZE_SEGMENT);
            string numRight = AnalyzeJson(buffer, "NumRight:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + NUMBER_OF_GAMES_SIZE_SEGMENT, NUM_RIGHT_SIZE_SEGMENT);
            string numWrong = AnalyzeJson(buffer, "NumWrong:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + NUMBER_OF_GAMES_SIZE_SEGMENT + NUM_RIGHT_SIZE_SEGMENT, NUM_WRONG_SIZE_SEGMENT);
            string avgTimePerAns = AnalyzeJson(buffer, "AvgTimePerAns:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + NUMBER_OF_GAMES_SIZE_SEGMENT + NUM_RIGHT_SIZE_SEGMENT + NUM_WRONG_SIZE_SEGMENT, AVG_TIME_PER_ANSWER_SIZE_SEGMENT);
            return new Status(numberOfGames, numRight, numWrong, avgTimePerAns);
        }


        public void FillNames(Room room, byte[] buffer, int startFrom)
        {
            bool stay = true;
            int j = 0;
            for (int i = startFrom; i < buffer.Length && stay; i++)
            {
                if(buffer[i] == '"')
                {
                    int end = FindStrIndex("\"", buffer, i + 2) - 1;
                    string name = GetBytes(i + 1, end - i - 1, buffer);
                    room._names[j] = name;
                    j++;
                    i = end;

                }
            }
        }

        public Question DeserializeGetQuestionResponse(byte[] buffer)
        {
            _dataLocationSign = 1;
            string status = AnalyzeJson(buffer, "Status:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT, STATUS_SIZE_SEGMENT);
            string question = AnalyzeJson(buffer, "Question:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT, QUESTION_SIZE_SEGMENT);
            Question qu = new Question(status, question);
            FillAnswers(qu, buffer, FindStrIndex("{", buffer, (FindStrIndex("{", buffer, 1)) + 1));
            return qu;
        }

        public void FillAnswers(Question qu, byte[] buffer, int startFrom)
        {
            bool stay = true;
            for (int i = startFrom; i < buffer.Length && stay; i++)
            {
                if (buffer[i] == '"')
                {
                    int idEnd = FindStrIndex("\"", buffer, i + 2) - 1;
                    string id = GetBytes(i + 1, idEnd - i - 1, buffer);

                    i = FindStrIndex(":", buffer, i);
                    int answerStart = FindStrIndex("\"", buffer, i);
                    int answerEnd = FindStrIndex("\"", buffer, answerStart+1) - 1;
                    string answer = GetBytes(answerStart, answerEnd - answerStart, buffer);
                    qu._answers.Add(Int32.Parse(id), answer);
                    i = answerEnd;
                }
            }
        }

        public Answer DeserializeSubmitAnswerRespone(byte[] buffer)
        {
            _dataLocationSign = 1;
            string status = AnalyzeJson(buffer, "Status:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT, STATUS_SIZE_SEGMENT);
            string correctAnswer = AnalyzeJson(buffer, "CorrectAnswerId:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT + STATUS_SIZE_SEGMENT, CORRECT_ANSWER_SIZE_SEGMENT);
            return new Answer(status, Int32.Parse(correctAnswer));
        }

        public Results DeserializeGetGameResultsRespone(byte[] buffer)
        {
            _dataLocationSign = 1;
            string status = AnalyzeJson(buffer, "Status:", _dataLocationSign, CODE_SEGMENT + DATA_LENGTH_SEGMENT, STATUS_SIZE_SEGMENT);
            Results res = new Results(status);
            FillResults(res, buffer, FindStrIndex("[", buffer, 1));
            return res;
        }

        public void FillResults(Results res, byte[] buffer, int startFrom)
        {
            bool stay = true;
            for (int i = startFrom; i < buffer.Length && stay; i++)
            {
                if (buffer[i] == '{')
                {
                    int usernameStart = FindStrIndex("\"", buffer, i);
                    int usernameEnd = FindStrIndex("\"", buffer, usernameStart) - 1;
                    string username = GetBytes(usernameStart, usernameEnd - usernameStart - 1, buffer);

                    i = FindStrIndex(",", buffer, i);
                    int scoreStart = FindStrIndex("\"", buffer, i);
                    int scoreEnd = FindStrIndex("\"", buffer, scoreStart) - 1;
                    string score = GetBytes(scoreStart + 1, scoreEnd - scoreStart, buffer);
                    res._resultsList.Add(new Score(username, score));
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
                ret += Convert.ToChar(buffer[i]);
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
