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
    /// Interaction logic for HighscoresWindow.xaml
    /// </summary>
    public partial class HighscoresWindow : Window
    {
        private Program _p;
        public HighscoresWindow(Program p)
        {
            Background = Brushes.AliceBlue;
            InitializeComponent();
            this._p = p;
            usernameTop.Text = this._p._username;
            usernameTop.Visibility = Visibility.Visible;
            changeScores();
        }

        public void changeScores()
        {
            Queue<KeyValuePair<string, int>> que = new Queue<KeyValuePair<string, int>>();
            string[] highScoresArr = this._p.GetHighScores();
            List<KeyValuePair<string, int>>results = new List<KeyValuePair<string, int>>();
            if (highScoresArr.Length!=0)
            {
                for (int i = 0; i < highScoresArr.Length; i++)
                {
                    bool flag = true;
                    int j = 0;
                    for (j = 0; j < highScoresArr[i].Length && flag; j++)
                    {
                        if (highScoresArr[i][j] == ':')
                        {
                            flag = false;
                        }
                    }

                    string name = highScoresArr[i].Substring(0, j - 1);
                    int score = Int32.Parse(highScoresArr[i].Substring(j, highScoresArr[i].Length - j));
                    results.Add(new KeyValuePair<string, int>(name, score));
                }
                results.Sort((x, y) => (y.Value.CompareTo(x.Value)));
                KeyValuePair<string, int> current =results[0];
                ChangeRank(current.Key, current.Value, first);
                current = results[1];
                ChangeRank(current.Key, current.Value, second);
                current = results[2];
                ChangeRank(current.Key, current.Value, third);

            }
        }


        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }


        private void ChangeRank(string name, int score, TextBlock place)
        {
            place.Text = name + "-" + score.ToString();
        }
    }
}
