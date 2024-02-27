using System;
using System.Collections.ObjectModel;
using ReactiveUI;
using RGRMileshko.Models;
using RGRMileshko.Models.Database;
using RGRMileshko.Models.StaticTabs;

namespace RGRMileshko.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        public MainWindowViewModel()
        {
            CreateContext();
            CreateTabs();
            CreateQueries();
            Content = Fv = new FirstViewModel(this);
            Sv = new SecondViewModel(this);
        }
        ViewModelBase content;
        public ViewModelBase Content
        {
            get { return content; }
            set { this.RaiseAndSetIfChanged(ref content, value); }
        }
        public void Change()
        {
            if (Content == Fv)
                Content = Sv;
            else if (Content == Sv)
                Content = Fv;
            else throw new InvalidOperationException();
        }

        ObservableCollection<MyTab> tabs;
        public ObservableCollection<MyTab> Tabs
        {
            get { return tabs; }
            set { this.RaiseAndSetIfChanged(ref tabs, value); }
        }

        ObservableCollection<Query> queries;
        public ObservableCollection<Query> Queries
        {
            get { return queries; }
            set { this.RaiseAndSetIfChanged(ref queries, value); }
        }

        public FirstViewModel Fv { get; }
        public SecondViewModel Sv { get; }

        NHLContext data;

        public NHLContext Data
        {
            get { return data; }
            set { this.RaiseAndSetIfChanged(ref data, value); }
        }
        private void CreateContext()
        {
            Data = new NHLContext();
        }

        private void CreateTabs()
        {
            Tabs = new ObservableCollection<MyTab>();
            Tabs.Add(new MatchTab("Match", Data.Matches));
            Tabs.Add(new PlayerStatisticTab ("PlayerStatistic", Data.PlayerStatistics));
            Tabs.Add(new PlayerTab("Player", Data.Players));
            Tabs.Add(new SeasonTab("Season", Data.Seasons));
            Tabs.Add(new TeamStatisticTab("TeamStatistic", Data.TeamStatistics));
            Tabs.Add(new TeamTab("Team", Data.Teams));
        }
        private void CreateQueries()
        {
            Queries = new ObservableCollection<Query>();
        }
    }
}
