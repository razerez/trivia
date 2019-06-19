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
        public WaitingRoomWindow(bool isManager)
        {
            InitializeComponent();
            if(isManager)
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
        }

        private void Change_Room_Name(string name)
        {
            roomName1.Text = name;
            roomName2.Text = "Room name: " + name;
        }

        private void Change_max_players(int max)
        {
            maxPlayers.Text = "max number of players: " + max.ToString();
        }

        private void Change_question_num(int num)
        {
            questionNum.Text = "number of questions: " + num.ToString();
        }

        private void Change_question_time(int time)
        {
            questionTime.Text = "time per question: " + time.ToString();
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            menu.Show();
            this.Close();
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            menu.Show();
            this.Close();
        }
    }
}
