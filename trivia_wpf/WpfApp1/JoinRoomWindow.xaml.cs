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
            if(rooms.Items.Count == 0)
            {
                error.Visibility = Visibility.Visible;
            }
            fillRoomList();
        }

        public bool JoinRoom()
        {
            return this._p.joinRoom(Int32.Parse(getRoomID()));
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
                    string roomID = System.Convert.ToInt32(roomsArr[p].Substring(roomsArr[p].Length - 1, 1)[0]).ToString();
                    string roomName = roomsArr[p].Substring(0, roomsArr[p].Length - 2);
                    Add_Room(roomID +". " + roomName);
                }
            }
        }


        public string getRoomID()
        {
            int len = 0;
            for (int i = 0; i < rooms.Text.Length; i++)
            {
                if (rooms.Text[i] == '.')
                {
                    len = i;
                    i = rooms.Text.Length;
                }
            }
            string roomId = rooms.Text.Substring(0, len);
            return roomId;
        }

        public void fillPlayerList()
        {
            string roomId = getRoomID();
            string[] playersArr = _p.getPlayersInRoom(Int32.Parse(roomId));

            for (int p = 0; p < playersArr.Length; p++)
            {
                string name = playersArr[p];
                Add_Player(name);
            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p, true);
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
            players.Items.Clear();
            rooms.SelectedItem = null;
            roomGrid.Visibility = Visibility.Hidden;
            JoinButton.IsEnabled = false;
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            if(!string.IsNullOrEmpty(rooms.Text))//check if room is selected
            {
                JoinRoom();
                WaitingRoomWindow waiting = new WaitingRoomWindow(this._p, false,"","","","");
                waiting.Show();
                this.Close();
            }
        }

        private void Rooms_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            JoinButton.IsEnabled = true;
            roomGrid.Visibility = Visibility.Visible;
            players.Items.Clear();
            fillPlayerList();
        }
    }
}
