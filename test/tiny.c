unsigned int rcu_read_lock() {
  return 0;
}

unsigned int rcu_read_unlock() {
  return 0;
}

void other() {
  rcu_read_lock();
  rcu_read_unlock();
}

int main() {
  rcu_read_lock();
  return 0;
}
