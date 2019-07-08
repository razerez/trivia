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
        private int _questionNum = 1;
        private int _numberOfQuestions;
        private int _score = 0;
        private int _userAnswer;
        private int _questionTime;
        private bool _gotAnswer;
        
        public GameWindow(Program p, int numberOfQuestions, int questionTime)
        {
            InitializeComponent();
            this._questionTime = questionTime;
            this._p = p;
            this._numberOfQuestions = numberOfQuestions;
            usernameTop.Text = this._p._username;
            _thS = new ThreadStart(GameThread);
            _th = new Thread(_thS);
            _th.IsBackground = true;
            _th.Start();
        }

        ~GameWindow()
        {
            this._killThread = true;
        }


        public void GameThread()
        {
            this._p.GetQuestion();
            while (!_killThread)
            {
                byte[] rec = this._p.ReciveMessage();
                if (rec[0] == 'q')
                {
                    this._gotAnswer = false;
                    countDown.Text = this._questionTime.ToString();
                    Thread timeThread = new Thread(new ThreadStart(DecCountDown));
                    timeThread.Start();

                    Question qu = new Deserializer().DeserializeGetQuestionResponse(rec);
                    this.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        questionNum.Text = "Question: " + this._questionNum + "/" + this._numberOfQuestions;
                        question.Text = qu._question;
                        option1.Content = qu._answers[1];
                        option2.Content = qu._answers[2];
                        option3.Content = qu._answers[3];
                        option4.Content = qu._answers[4];
                    }));
                }
                else if (rec[0] == 'a')
                {
                    this._gotAnswer = true;
                    Answer ans = new Deserializer().DeserializeSubmitAnswerRespone(rec);
                    this.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        if (ans._correctAnswer == this._userAnswer)
                        {
                            switch (ans._correctAnswer)
                            {
                                case (1):
                                    option1.Background = Brushes.LightGreen;
                                    break;
                                case (2):
                                    option2.Background = Brushes.LightGreen;
                                    break;
                                case (3):
                                    option3.Background = Brushes.LightGreen;
                                    break;
                                case (4):
                                    option4.Background = Brushes.LightGreen;
                                    break;
                            }
                            this._score++;
                            score.Text = "score: " + this._score;

                        }
                        else
                        {
                            switch (this._userAnswer)
                            {
                                case (1):
                                    option1.Background = Brushes.Red;
                                    break;
                                case (2):
                                    option2.Background = Brushes.Red;
                                    break;
                                case (3):
                                    option3.Background = Brushes.Red;
                                    break;
                                case (4):
                                    option4.Background = Brushes.Red;
                                    break;
                            }
                        }
                        Thread.Sleep(2000);
                        if (this._questionNum < this._questionTime)
                        {
                            this._p.GetQuestion();
                        }
                    }));
                }
                else if(rec[0] == 'z')
                {
                    this._killThread = true;
                    Results res = new Deserializer().DeserializeGetGameResultsRespone(rec);
                    ScoreboardWindow scoreboard = new ScoreboardWindow(res._resultsList);
                    scoreboard.Show();
                    Menu menu = new Menu(this._p, true);
                    menu.Show();
                    this.Close();
                }
            }
        }


        private void DecCountDown()
        {
            while(Int32.Parse(countDown.Text) != 0)
            {
                if (!this._gotAnswer)
                {
                    this.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        countDown.Text = (Int32.Parse(countDown.Text) - 1).ToString();
                    }));
                    Thread.Sleep(1000); //This is milliseconds
                }
                else
                {
                    countDown.Text = 0.ToString();
                }
                
            }
            if (!this._gotAnswer)
            {
                if (this._questionNum < this._questionTime)
                {
                    this._p.GetQuestion();
                }
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
            this._userAnswer = 1;
            this._p.SubmitAnswer("1");
        }            
                     
        private void Option2_Click(object sender, RoutedEventArgs e)
        {
            this._userAnswer = 2;
            this._p.SubmitAnswer("2");
        }            
                     
        private void Option3_Click(object sender, RoutedEventArgs e)
        {
            this._userAnswer = 3;
            this._p.SubmitAnswer("3");
        }            
                     
        private void Option4_Click(object sender, RoutedEventArgs e)
        {
            this._userAnswer = 4;
            this._p.SubmitAnswer("4");
        }
    }
}
