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

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for WaitingRoomWindow.xaml
    /// </summary>
    public partial class WaitingRoomWindow : Window
    {
        private Program _p;
        public WaitingRoomWindow(Program p, bool isManager, string roomName, string maxUsers, string questionNum, string questionTime)
        {
            InitializeComponent();
            this._p = p;
            usernameTop.Text = this._p._username;
            usernameTop.Visibility = Visibility.Visible;
            if (isManager)
            {
                start_button.Visibility = Visibility.Visible;
                closeButton.Visibility = Visibility.Visible;
                leave_button.Visibility = Visibility.Hidden;
            }
            else
            {
                start_button.Visibility = Visibility.Hidden;
                closeButton.Visibility = Visibility.Hidden;
                leave_button.Visibility = Visibility.Visible;
            }

            Change_Room_Name(roomName);
            Change_max_players(maxUsers);
            Change_question_num(questionNum);
            Change_question_time(questionTime);
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
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }
    }
}
