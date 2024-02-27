using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

namespace RGRMileshko.Models.Database
{
    public partial class NHLContext : DbContext
    {
        public NHLContext()
        {
        }

        public NHLContext(DbContextOptions<NHLContext> options)
        : base(options)
        {
        }

        public virtual DbSet<Match> Matches { get; set; } = null!;
        public virtual DbSet<Player> Players { get; set; } = null!;
        public virtual DbSet<PlayerStatistic> PlayerStatistics { get; set; } = null!;
        public virtual DbSet<Season> Seasons { get; set; } = null!;
        public virtual DbSet<Team> Teams { get; set; } = null!;
        public virtual DbSet<TeamStatistic> TeamStatistics { get; set; } = null!;

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
#warning To protect potentially sensitive information in your connection string, you should move it out of source code. You can avoid scaffolding the connection string by using the Name= syntax to read it from configuration - see https://go.microsoft.com/fwlink/?linkid=2131148. For more guidance on storing connection strings, see http://go.microsoft.com/fwlink/?LinkId=723263.
                optionsBuilder.UseSqlite("Data Source=C:\\Users\\Alex\\source\\repos\\RGRMileshko\\RGRMileshko\\Assets\\NHL.db");
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Match>(entity =>
            {
                entity.HasKey(e => e.GameNumber);

                entity.ToTable("Match");

                entity.Property(e => e.GameNumber)
                .ValueGeneratedNever()
                .HasColumnName("Game Number");

                entity.Property(e => e.SeasonYear).HasColumnName("Season Year");

                entity.HasOne(d => d.SeasonYearNavigation)
                .WithMany(p => p.Matches)
                .HasForeignKey(d => d.SeasonYear);
            });

            modelBuilder.Entity<Player>(entity =>
            {
                entity.HasKey(e => e.Name);

                entity.ToTable("Player");

                entity.Property(e => e.TeamName).HasColumnName("Team Name");

                entity.Property(e => e.YearFrom).HasColumnName("Year from");

                entity.Property(e => e.YearTo).HasColumnName("Year to");

                entity.HasOne(d => d.TeamNameNavigation)
                .WithMany(p => p.Players)
                .HasForeignKey(d => d.TeamName);
            });

            modelBuilder.Entity<PlayerStatistic>(entity =>
            {
                entity.HasKey(e => e.NumberPlayerStatistic);

                entity.ToTable("Player_Statistic");

                entity.Property(e => e.NumberPlayerStatistic)
                .ValueGeneratedNever()
                .HasColumnName("Number_Player_Statistic");

                entity.Property(e => e.CorsiAgainst).HasColumnName("Corsi-against");

                entity.Property(e => e.CorsiFor).HasColumnName("Corsi-for");

                entity.Property(e => e.GameNumber).HasColumnName("Game Number");

                entity.Property(e => e.PlayerName).HasColumnName("Player_Name");

                entity.Property(e => e.ShotsAttempted).HasColumnName("Shots attempted");

                entity.HasOne(d => d.GameNumberNavigation)
                .WithMany(p => p.PlayerStatistics)
                .HasForeignKey(d => d.GameNumber);

                entity.HasOne(d => d.PlayerNameNavigation)
                .WithMany(p => p.PlayerStatistics)
                .HasForeignKey(d => d.PlayerName);
            });

            modelBuilder.Entity<Season>(entity =>
            {
                entity.HasKey(e => e.YearFrom);

                entity.ToTable("Season");

                entity.Property(e => e.YearFrom)
                .ValueGeneratedNever()
                .HasColumnName("Year from");

                entity.Property(e => e.RunnerUp).HasColumnName("Runner-Up");

                entity.Property(e => e.YearTo).HasColumnName("Year to");

                entity.HasOne(d => d.RunnerUpNavigation)
                .WithMany(p => p.SeasonRunnerUpNavigations)
                .HasForeignKey(d => d.RunnerUp);

                entity.HasOne(d => d.WinnerNavigation)
                .WithMany(p => p.SeasonWinnerNavigations)
                .HasForeignKey(d => d.Winner);
            });

            modelBuilder.Entity<Team>(entity =>
            {
                entity.HasKey(e => e.TeamName);

                entity.ToTable("Team");

                entity.Property(e => e.TeamName).HasColumnName("Team Name");

                entity.Property(e => e.YearFrom).HasColumnName("Year from");

                entity.Property(e => e.YearTo).HasColumnName("Year to");
            });

            modelBuilder.Entity<TeamStatistic>(entity =>
            {
                entity.HasKey(e => e.NumberTeamStatistic);

                entity.ToTable("Team_Statistic");

                entity.Property(e => e.NumberTeamStatistic)
                .ValueGeneratedNever()
                .HasColumnName("Number_Team_Statistic");

                entity.Property(e => e.GameNumber).HasColumnName("Game Number");

                entity.Property(e =>
                e.GoalsAgainst).HasColumnName("Goals against");

                entity.Property(e => e.GoalsFor).HasColumnName("Goals for");

                entity.Property(e => e.MatchResult).HasColumnName("Match Result");

                entity.Property(e => e.ShotsAgainst).HasColumnName("Shots against");

                entity.Property(e => e.ShotsFor).HasColumnName("Shots for");

                entity.Property(e => e.TeamName).HasColumnName("Team Name");

                entity.HasOne(d => d.GameNumberNavigation)
                .WithMany(p => p.TeamStatistics)
                .HasForeignKey(d => d.GameNumber);

                entity.HasOne(d => d.TeamNameNavigation)
                .WithMany(p => p.TeamStatistics)
                .HasForeignKey(d => d.TeamName);
            });

            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}
