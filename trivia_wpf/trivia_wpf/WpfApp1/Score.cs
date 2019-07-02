using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    public class Score
    {
        public string _username;
        public string _score;
        public Score(string username, string score)
        {
            this._username = username;
            this._score = score;
        }
    }
}
