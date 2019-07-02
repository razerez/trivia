using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    public class Answer
    {
        public string _status;
        public int _correctAnswer;
        public Answer(string status, int correctAnswer)
        {
            this._status = status;
            this._correctAnswer = correctAnswer;
        }
    }
}
