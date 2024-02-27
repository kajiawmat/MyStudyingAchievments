using ReactiveUI;
using System.Reactive;
using RGRMileshko.Models;

namespace RGRMileshko.ViewModels
{
    public class SelectDBViewModel : ViewModelBase
    {
        public SelectDBViewModel(MainWindowViewModel? mainContext = null)
        {
            MainContext = mainContext;
            ButtonChangeTable = ReactiveCommand.Create<MyTab, Unit>((tab) =>
            {
                SelectedTab = tab;
                return Unit.Default;
            });
        }
        public MainWindowViewModel? MainContext { get; set; }
        MyTab selectedTab;
        public MyTab SelectedTab
        {
            get { return selectedTab; }
            set { this.RaiseAndSetIfChanged(ref selectedTab, value); }
        }

        string where = @"";
        public string Where
        {
            get { return where; }
            set { this.RaiseAndSetIfChanged(ref where, value); }
        }
        public ReactiveCommand<MyTab, Unit> ButtonChangeTable { get; }
    }
}
