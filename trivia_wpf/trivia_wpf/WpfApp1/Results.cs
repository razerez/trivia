using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    public class Results
    {
        public string _status;
        public List<Score> _resultsArr;
        public Results(string status)
        {
            this._status = status;
            this._resultsArr = new List<Score>();
        }
    }
}
