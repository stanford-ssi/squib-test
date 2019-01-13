#include <functional>

#define JOB_QUEUE_MAX 256
class JobQueue {
public:
  typedef enum {
    HIGH_PRIORITY = 0,
    REGULAR_PRIORITY = 1,
    LOW_PRIORITY = 2
  } priority_t;
  void loop();
  bool schedule(
    std::function<void()> task,
    priority_t priority = REGULAR_PRIORITY
  );
  bool empty() const;
  bool full() const;
private:
  typedef struct {
    priority_t priority;
    std::function<void ()> task;
  } job_t;
  job_t todo[JOB_QUEUE_MAX];
  size_t head; // points to first valid job
  size_t tail; // points to first empty space
};

/*
JobQueue Q;
int main() {
  Q.schedule([]{std::cout << "Hello!" << std::endl;});
  Q.schedule([]{std::cout << "Goodbye!" << std::endl;}, JobQueue::HIGH_PRIORITY);
  while (true) {
    Q.loop();
  }
}
*/
