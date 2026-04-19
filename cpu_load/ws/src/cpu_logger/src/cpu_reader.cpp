#include <fstream>
#include <vector>

class CpuReader
{
public:
    double getCpuUsage()
    {
        return readCpuUsage();
    }

private:
    typedef std::vector<double> CpuTimesVec;
    CpuTimesVec lastReadTimes;

    double readCpuUsage()
    {
        CpuTimesVec old_times = lastReadTimes;
        lastReadTimes = getCpuTimes();
        if (old_times.empty())
        {
            for (size_t i=0; i < lastReadTimes.size(); i++)
            {
                old_times.push_back(0);
            }
        }
        return calcUsage(old_times, lastReadTimes);
    }

    static CpuTimesVec getCpuTimes()
    {
        // Retrieves current times the CPU spend in each feasible state
        std::ifstream f("/host_proc/stat");
        f.ignore(5, ' ');
        CpuTimesVec times;
        for (double time; f >> time; times.push_back(time)) {}
        return times;
    }

    static double calcUsage(const CpuTimesVec& old, const CpuTimesVec& current)
    {
        // Calculates total usage/load
        const double idle_time_diff = current[3] - old[3];
        double total = 0;
        double old_total = 0;
        for (size_t i =0; i < old.size(); i++)
        {
            old_total += old[i];
            total += current[i];
        }
        double total_diff = total - old_total;
        // Calcualte relative time not spent in IDLE state
        return 100-(idle_time_diff/total_diff) * 100.0;
    }
};