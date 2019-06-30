using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Threading;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for WaitingRoomWindow.xaml
    /// </summary>
    public partial class WaitingRoomWindow : Window
    {
        private Program _p;
        private ThreadStart _thS;
        private Thread _th;
        private bool _isClosed = false;
        private bool _hasLeft = false;
        private bool _killThread = false;
        bool _isManager;
        public WaitingRoomWindow(Program p, bool isManager, string roomName, string maxUsers, string questionNum, string questionTime, string[] players)
        {
            InitializeComponent();
            this._p = p;
            this._isManager = isManager;
            usernameTop.Text = this._p._username;
            usernameTop.Visibility = Visibility.Visible;
            if (isManager)
            {
                start_button.Visibility = Visibility.Visible;
                closeButton.Visibility = Visibility.Visible;
                leave_button.Visibility = Visibility.Hidden;
                Change_max_players(maxUsers);
            }
            else
            {
                roomName2.Visibility = Visibility.Hidden;
                maxPlayers.Visibility = Visibility.Hidden;

                start_button.Visibility = Visibility.Hidden;
                closeButton.Visibility = Visibility.Hidden;
                leave_button.Visibility = Visibility.Visible;
            }

            Change_Room_Name(roomName);
            Change_question_num(questionNum);
            Change_question_time(questionTime);
            UpdatePlayers(players);

            _thS = new ThreadStart(MainThread);
            _th = new Thread(_thS);
            _th.IsBackground = true;
            _th.Start();
        }

        ~WaitingRoomWindow()
        {
            if(this._isManager && !this._isClosed)
            {
                this._p.CloseRoom();
            }
            if(!this._hasLeft)
            {
                this._p.LeaveRoom();
            }
            _killThread = true;
        }

        public void MainThread()
        {
            while (!_killThread)
            {
                byte[] rec = this._p.ReciveMessage();
                if (rec[0] == 'p')
                {
                    string[] players = this._p.DecodeArrMessage(rec);
                    this.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        UpdatePlayers(players);
                    }));
                }
                else if(rec[0] == 'd')
                {
                    _killThread = true;
                    if(!this._isManager)
                    {
                        this.Dispatcher.BeginInvoke(new Action(() =>
                        {
                            error.Visibility = Visibility.Visible;
                        }));
                        this._isClosed = true;
                    }
                }
                else if(rec[0] == 's')
                {
                    _killThread = true;
                    //start
                }
                else
                { 
                    _killThread = true;
                }
            }
        }



        public void UpdatePlayers(string[] players)
        {
            participants.Items.Clear();
            for (int i = 0; i < players.Length; i++)
            {
                participants.Items.Add(players[i]);
            }
        }


        private void Change_Room_Name(string name)
        {
            roomName1.Text = name;
            roomName2.Text = "Room name: " + name;
        }

        private void Change_max_players(string max)
        {
            maxPlayers.Text = "max number of players: " + max;
        }

        private void Change_question_num(string num)
        {
            questionNum.Text = "number of questions: " + num;
        }

        private void Change_question_time(string time)
        {
            questionTime.Text = "time per question: " + time;
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            this._p.CloseRoom();
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            this._p.StartGame();
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            if (!_isClosed)
            {
                _p.LeaveRoom();
            }
            this._hasLeft = true;
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }
    }
}
