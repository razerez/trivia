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
        public List<Score> _resultsList;
        public Results(string status)
        {
            this._status = status;
            this._resultsList = new List<Score>();
        }
    }
}
