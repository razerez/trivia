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
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        private Program _p;
        private ThreadStart _thS;
        private Thread _th;
        private bool _killThread = false;
        public GameWindow(Program p)
        {
            InitializeComponent();
            this._p = p;
            usernameTop.Text = this._p._username;
            _thS = new ThreadStart(GameThread);
            _th = new Thread(_thS);
            _th.IsBackground = true;
            _th.Start();
        }


        public void GameThread()
        {
            byte[] rec = this._p.ReciveMessage();
            if(rec[0] == 'q')
            {

            }
        }


        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }

        private void Option1_Click(object sender, RoutedEventArgs e)
        {
            this._p.SubmitAnswer("1");
        }            
                     
        private void Option2_Click(object sender, RoutedEventArgs e)
        {
            this._p.SubmitAnswer("2");
        }            
                     
        private void Option3_Click(object sender, RoutedEventArgs e)
        {
            this._p.SubmitAnswer("3");
        }            
                     
        private void Option4_Click(object sender, RoutedEventArgs e)
        {
            this._p.SubmitAnswer("4");
        }
    }
}
