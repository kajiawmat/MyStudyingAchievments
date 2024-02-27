using ReactiveUI;
using System.Reactive;
using RGRMileshko.Models;

namespace RGRMileshko.ViewModels
{
    public class JoinDBViewModel : ViewModelBase
    {
        public JoinDBViewModel(MainWindowViewModel? mainContext = null)
        {
            MainContext = mainContext;
            ButtonChangeTableFirst = ReactiveCommand.Create<MyTab, Unit>((tab) =>
            {
                FirstSelectedTab = tab;
                FirstSelectedField = "";
                return Unit.Default;
            });
            ButtonChangeTableSecond = ReactiveCommand.Create<MyTab, Unit>((tab) =>
            {
                SecondSelectedTab = tab;
                SecondSelectedField = "";
                return Unit.Default;
            });
            ButtonChangeJoinFirst = ReactiveCommand.Create<string, Unit>((str) =>
            {
                FirstSelectedField = str;
                return Unit.Default;
            });
            ButtonChangeJoinSecond = ReactiveCommand.Create<string, Unit>((str) =>
            {
                SecondSelectedField = str;
                return Unit.Default;
            });
        }
        public MainWindowViewModel? MainContext { get; set; }
        MyTab firstSelectedTab;
        public MyTab FirstSelectedTab
        {
            get { return firstSelectedTab; }
            set { this.RaiseAndSetIfChanged(ref firstSelectedTab, value); }
        }
        MyTab secondSelectedTab;
        public MyTab SecondSelectedTab
        {
            get { return secondSelectedTab; }
            set { this.RaiseAndSetIfChanged(ref secondSelectedTab, value); }
        }
        string firstSelectedField;
        public string FirstSelectedField
        {
            get { return firstSelectedField; }
            set { this.RaiseAndSetIfChanged(ref firstSelectedField, value); }
        }
        string secondSelectedField;
        public string SecondSelectedField
        {
            get { return secondSelectedField; }
            set { this.RaiseAndSetIfChanged(ref secondSelectedField, value); }
        }
        public ReactiveCommand<MyTab, Unit> ButtonChangeTableFirst { get; }
        public ReactiveCommand<MyTab, Unit> ButtonChangeTableSecond { get; }
        public ReactiveCommand<string, Unit> ButtonChangeJoinFirst { get; }
        public ReactiveCommand<string, Unit> ButtonChangeJoinSecond { get; }
    }
}
