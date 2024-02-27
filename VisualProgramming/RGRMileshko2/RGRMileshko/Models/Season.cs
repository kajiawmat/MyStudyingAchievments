using System;
using System.Collections.Generic;

namespace RGRMileshko.Models.Database
{
    public partial class Season
    {
        public Season()
        {
            Matches = new HashSet<Match>();
        }

        public string YearFrom { get; set; } = null!;
        public string? YearTo { get; set; }
        public string? Winner { get; set; }
        public string? RunnerUp { get; set; }

        public virtual Team? RunnerUpNavigation { get; set; }
        public virtual Team? WinnerNavigation { get; set; }
        public virtual ICollection<Match> Matches { get; set; }
    }
}
