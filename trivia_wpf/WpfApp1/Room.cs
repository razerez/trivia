using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    class Room
    {
        public string questionCount;
        public string answerTime;
        public Room(string questionCount, string answerTime)
        {
            this.questionCount = questionCount;
            this.answerTime = answerTime;
        }
    }
}
