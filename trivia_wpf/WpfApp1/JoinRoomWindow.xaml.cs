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
            usernameTop.Text = this._p._username;
            usernameTop.Visibility = Visibility.Visible;
            if (rooms.Items.Count == 0)
            {
                error.Visibility = Visibility.Visible;
            }
            fillRoomList();
        }

        public bool JoinRoom()
        {
            int id;
            bool res=Int32.TryParse(getRoomID(), out id);
            if (res == false)
                return false;
            return this._p.JoinRoom(id);
        }

        public void fillRoomList()
        {
            rooms.Items.Clear();
            string[] roomsArr = _p.GetRooms();
            if (roomsArr.Length == 0)
                error.Visibility = Visibility.Visible;
            else
            {
                error.Visibility = Visibility.Hidden;
                for (int i = 0; i < roomsArr.Length; i++)
                {
                    bool flag=true;
                    int colPlace=0;
                    for (int j = 0; j < roomsArr[i].Length&&flag; j++)
                    {
                        if (roomsArr[i][j] == ':')
                        {
                            flag = false;
                            colPlace = j;
                        }
                    }
                    string roomName = roomsArr[i].Substring(0, colPlace);
                    string roomID = roomsArr[i].Substring(colPlace+1,roomsArr[i].Length-colPlace-1);
                    Add_Room(roomID +". " + roomName);
                }
            }
        }


        public string getRoomID()
        {
            int len = 0;
            string selection = rooms.SelectedValue.ToString();
            for (int i = 0; i < selection.Length; i++)
            {
                if (selection[i] == '.')
                {
                    len = i;
                    i = selection.Length;
                }
            }
            string roomId = selection.Substring(0, len);
            return roomId;
        }

        public string GetRoomName()
        {
            string name = rooms.SelectedItem.ToString();
            name = name.Substring((rooms.SelectedItem.ToString().IndexOf(". ")) + 2, rooms.SelectedItem.ToString().Length - 3);
            return name;
        }

        public void fillPlayerList()
        {
            players.Items.Clear();
            string[] roomsArr = _p.GetRooms();
            if (roomsArr.Length == 0)
                error.Visibility = Visibility.Visible;
            else
            {
                error.Visibility = Visibility.Hidden;
                for (int i = 0; i < roomsArr.Length; i++)
                {
                    bool flag = true;
                    int colPlace = 0;
                    for (int j = 0; j < roomsArr[i].Length && flag; j++)
                    {
                        if (roomsArr[i][j] == ':')
                        {
                            flag = false;
                            colPlace = j;
                        }
                    }
                    string roomName = roomsArr[i].Substring(0, colPlace);
                    string roomID = roomsArr[i].Substring(colPlace + 1, roomsArr[i].Length - colPlace - 1);
                    Add_Room(roomID + ". " + roomName);
                }
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
            fillRoomList();
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            if(!string.IsNullOrEmpty(rooms.Text))//check if room is selected
            {
                JoinRoom();
                Room room = this._p.GetRoomState();
                WaitingRoomWindow waiting = new WaitingRoomWindow(this._p, false,GetRoomName()
                                                                , "", room._questionCount, room._answerTime, room._names);
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
