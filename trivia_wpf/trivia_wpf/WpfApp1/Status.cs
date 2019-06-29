using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    public class Status
    {
        public string _numberOfGames;
        public string _numRight;
        public string _numWrong;
        public string _avgTimePerAns;
        public Status(string numberOfGames, string numRight, string numWrong, string avgTimePerAns)
        {
            this._numberOfGames = numberOfGames;
            this._numRight = numRight;
            this._numWrong = numWrong;
            this._avgTimePerAns = avgTimePerAns;
        }
    }
}
