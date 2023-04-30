#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class JobQueue {
 private:
  int num_workers_;
  std::vector<int> jobs_;

  std::vector<int> assigned_workers_;
  std::vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i)
      std::cout << assigned_workers_[i] << " " << start_times_[i] << std::endl;
  }

  void ReadData() {
    int m;
    std::cin >> num_workers_ >> m;
    jobs_.resize(m);
    for (int i = 0; i < m; ++i)
      std::cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    // TODO: replace this code with a faster algorithm.
    // std::vector<long long> next_free_time(num_workers_, 0);
    // for (int i = 0; i < jobs_.size(); ++i) {
    //   int duration = jobs_[i];
    //   int next_worker = 0;
    //   for (int j = 0; j < num_workers_; ++j)
    //     if (next_free_time[j] < next_free_time[next_worker])
    //       next_worker = j;
    //
    //   assigned_workers_[i] = next_worker;
    //   start_times_[i] = next_free_time[next_worker];
    //   next_free_time[next_worker] += duration;
    // }

    // Priority queue to store the next available worker
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> next_free_time;

    // Initially, add the first 'num_workers_' workers to the priority queue
    for (int i = 0; i < num_workers_; ++i)
      next_free_time.emplace(0, i);

    // Process each job and assign it to the next available worker
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];

      // Get the next available worker and the time when the worker will be free
      auto next_worker = next_free_time.top();
      next_free_time.pop();

      int worker_idx = next_worker.second;
      long long start_time = next_worker.first;

      // Assign the job to the worker and update the worker's next free time
      assigned_workers_[i] = worker_idx;
      start_times_[i] = start_time;
      next_free_time.emplace(start_time + duration, worker_idx);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
