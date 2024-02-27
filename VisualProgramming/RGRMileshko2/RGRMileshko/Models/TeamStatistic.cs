using System;
using System.Collections.Generic;

namespace RGRMileshko.Models.Database
{
    public partial class TeamStatistic
    {
        public long NumberTeamStatistic { get; set; }
        public long? GameNumber { get; set; }
        public string? TeamName { get; set; }
        public string? MatchResult { get; set; }
        public long? GoalsFor { get; set; }
        public long? GoalsAgainst { get; set; }
        public long? ShotsFor { get; set; }
        public long? ShotsAgainst { get; set; }

        public virtual Match? GameNumberNavigation { get; set; }
        public virtual Team? TeamNameNavigation { get; set; }
    }
}
