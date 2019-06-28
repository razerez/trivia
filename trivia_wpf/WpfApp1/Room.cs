﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    public class Room
    {
        public string _status;
        public string _hasStarted;
        public string _questionCount;
        public string _answerTime;
        public int _length;
        public string[] _names;
        public Room(string status, string hasStarted, string questionCount, string answerTime, int length)
        {
            this._status = status;
            this._hasStarted = hasStarted;
            this._questionCount = questionCount;
            this._answerTime = answerTime;
            this._length = length;
            this._names = new string[length];
        }
    }
}
