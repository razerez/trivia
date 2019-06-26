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
            InitializeComponent();
            this._p = p;
            changeScores();
        }

        public void changeScores()
        {
            Queue<KeyValuePair<string, int>> que = new Queue<KeyValuePair<string, int>>();

            string[] highScoresArr = this._p.getHighScores();
            if(highScoresArr.Length!=0)
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
                    string score = highScoresArr[i].Substring(j, highScoresArr[i].Length - j);
                    que.Enqueue(new KeyValuePair<string, int>(name, Int32.Parse(score)));
                }
                ChangeRank(que.Dequeue().Key, que.Dequeue().Value, first);
                ChangeRank(que.Dequeue().Key, que.Dequeue().Value, second);
                ChangeRank(que.Dequeue().Key, que.Dequeue().Value, third);
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
