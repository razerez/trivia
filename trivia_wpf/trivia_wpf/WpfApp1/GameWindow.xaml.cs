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
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        private Program _p;
        public GameWindow(Program p)
        {
            InitializeComponent();
            this._p = p;
            usernameTop.Text = this._p._username;
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }

        private void Option1_Click(object sender, RoutedEventArgs e)
        {            
                    
        }            
                     
        private void Option2_Click(object sender, RoutedEventArgs e)
        {            
                    
        }            
                     
        private void Option3_Click(object sender, RoutedEventArgs e)
        {            
                     
        }            
                     
        private void Option4_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
