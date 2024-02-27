using System;
using System.Collections.Generic;

namespace RGRMileshko.Models.Database
{
    public partial class Match
    {
        public Match()
        {
            PlayerStatistics = new HashSet<PlayerStatistic>();
            TeamStatistics = new HashSet<TeamStatistic>();
        }

        public long GameNumber { get; set; }
        public string? SeasonYear { get; set; }
        public string? Date { get; set; }
        public string? Arena { get; set; }

        public virtual Season? SeasonYearNavigation { get; set; }
        public virtual ICollection<PlayerStatistic> PlayerStatistics { get; set; }
        public virtual ICollection<TeamStatistic> TeamStatistics { get; set; }
    }
}
