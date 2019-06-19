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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        private Program _p;
        public JoinRoomWindow(Program p)
        {
            InitializeComponent();
            this._p = p;
        }

        public void fillRoomList()
        {
            string[] roomsArr = _p.getRooms();
            if (roomsArr.Length == 0)
                error.Visibility = Visibility.Visible;
            else
            {
                error.Visibility = Visibility.Hidden;
                for (int p = 0; p < roomsArr.Length; p++)
                {
                    string roomName = roomsArr[p].Substring(0, roomsArr[p].Length - 2);
                    Add_Room(roomName);
                }
            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p);
            menu.Show();
            this.Close();
        }

        private void Add_Room(string name)
        {
            rooms.Items.Add(name);
        }

        private void Add_Player(string name)
        {
            players.Items.Add(name);
        }
        private void Refresh_Click(object sender, RoutedEventArgs e)
        {
            rooms.SelectedItem = null;
            roomGrid.Visibility = Visibility.Hidden;
            JoinButton.IsEnabled = false;
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            if(!string.IsNullOrEmpty(rooms.Text))//check if room is selected
            {
                WaitingRoomWindow waiting = new WaitingRoomWindow(this._p, false);
                waiting.Show();
                this.Close();
            }
        }

        private void Rooms_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            JoinButton.IsEnabled = true;
            roomGrid.Visibility = Visibility.Visible;
        }
    }
}
