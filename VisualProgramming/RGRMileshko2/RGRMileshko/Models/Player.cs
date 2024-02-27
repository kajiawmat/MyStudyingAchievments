using System;
using System.Collections.Generic;

namespace RGRMileshko.Models.Database
{
    public partial class Player
    {
        public Player()
        {
            PlayerStatistics = new HashSet<PlayerStatistic>();
        }

        public string Name { get; set; } = null!;
        public string? TeamName { get; set; }
        public long? Age { get; set; }
        public string? Position { get; set; }
        public long? Height { get; set; }
        public long? Weight { get; set; }
        public string? Country { get; set; }
        public string? YearFrom { get; set; }
        public string? YearTo { get; set; }

        public virtual Team? TeamNameNavigation { get; set; }
        public virtual ICollection<PlayerStatistic> PlayerStatistics { get; set; }
    }
}
