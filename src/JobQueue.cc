#include "JobQueue.h"
#include "Arduino.h"

void JobQueue::loop() {
  noInterrupts();

  if (empty()) {
    interrupts();
    return;
  }
  job_t job = todo[head];
  head = (head + 1) % JOB_QUEUE_MAX;
  interrupts();

  if (job.when <= millis()) {
    job.task();
    if (job.priority == RECURRING_PRIORITY) {
      schedule(job.task, RECURRING_PRIORITY, job.when + job.delay, job.delay);
    }
  } else {
    if (job.priority == RECURRING_PRIORITY) {
      schedule(job.task, RECURRING_PRIORITY, job.when, job.delay);
    }
  }
}

bool JobQueue::schedule(
  std::function<void()> task,
  priority_t priority,
  uint32_t when,
  uint32_t delay
) {
  noInterrupts();

  if (full()) {
    interrupts();
    return false;
  };
  size_t cursor = tail;
  while (cursor != head) {
    size_t prev = (cursor - 1) % JOB_QUEUE_MAX;
    if (todo[prev].priority > priority) {
      todo[cursor] = todo[(cursor - 1) % JOB_QUEUE_MAX];
    } else break;
    cursor = prev;
  }

  todo[cursor].priority = priority;
  todo[cursor].when = when;
  todo[cursor].delay = delay;
  todo[cursor].task = task;

  tail = (tail + 1) % JOB_QUEUE_MAX;
  interrupts();

  return true;
}

bool JobQueue::empty() const {
  return head == tail;
}

bool JobQueue::full() const {
  return (tail + 1) % JOB_QUEUE_MAX == head;
}
