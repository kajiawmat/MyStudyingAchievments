using ReactiveUI;
using System.Reactive;
using RGRMileshko.Models;

namespace RGRMileshko.ViewModels
{
    public class SecondViewModel : ViewModelBase
    {
        public SecondViewModel(MainWindowViewModel? mainContext = null)
        {
            MainContext = mainContext;
            ButtonDeleteQuery = ReactiveCommand.Create<Query, Unit>((query) =>
            {
                MainContext.Queries.Remove(query);
                MainContext.Tabs.Remove(query.BindedTab);
                if (QueryDescription == query.Description)
                    QueryDescription = "";
                return Unit.Default;
            });
            ButtonShowQuery = ReactiveCommand.Create<Query, Unit>((query) =>
            {
                QueryDescription = query.Description;
                return Unit.Default;
            });
        }
        string queryDescription = "";
        public string QueryDescription
        {
            get { return queryDescription; }
            set { this.RaiseAndSetIfChanged(ref queryDescription, value); }
        }
        public ReactiveCommand<Query, Unit> ButtonDeleteQuery { get; }
        public ReactiveCommand<Query, Unit> ButtonShowQuery { get; }
        public MainWindowViewModel? MainContext { get; set; }
    }
}
