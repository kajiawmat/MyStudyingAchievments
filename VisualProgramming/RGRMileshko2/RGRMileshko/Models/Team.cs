using System;
using System.Collections.Generic;

namespace RGRMileshko.Models.Database
{
    public partial class Team
    {
        public Team()
        {
            Players = new HashSet<Player>();
            SeasonRunnerUpNavigations = new HashSet<Season>();
            SeasonWinnerNavigations = new HashSet<Season>();
            TeamStatistics = new HashSet<TeamStatistic>();
        }

        public string TeamName { get; set; } = null!;
        public string? Division { get; set; }
        public string? YearFrom { get; set; }
        public string? YearTo { get; set; }

        public virtual ICollection<Player> Players { get; set; }
        public virtual ICollection<Season> SeasonRunnerUpNavigations { get; set; }
        public virtual ICollection<Season> SeasonWinnerNavigations { get; set; }
        public virtual ICollection<TeamStatistic> TeamStatistics { get; set; }
    }
}
