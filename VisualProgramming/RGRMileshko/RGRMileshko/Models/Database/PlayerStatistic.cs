using System;
using System.Collections.Generic;

namespace RGRMileshko.Models.Database
{
    public partial class PlayerStatistic
    {
        public long NumberPlayerStatistic { get; set; }
        public long? GameNumber { get; set; }
        public string? PlayerName { get; set; }
        public long? Goals { get; set; }
        public long? ShotsAttempted { get; set; }
        public long? CorsiFor { get; set; }
        public long? CorsiAgainst { get; set; }
        public long? Takeaways { get; set; }
        public long? Giveaways { get; set; }

        public virtual Match? GameNumberNavigation { get; set; }
        public virtual Player? PlayerNameNavigation { get; set; }
    }
}
