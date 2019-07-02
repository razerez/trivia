using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    public class Question
    {
        public string _status;
        public string _question;
        public Dictionary<int, string> _answers;
        public Question(string status, string question)
        {
            this._status = status;
            this._question = question;
            this._answers = new Dictionary<int, string>();
        }
    }
}
