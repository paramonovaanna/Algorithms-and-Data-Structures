#include <climits>
#include <iostream>
#include <queue>

struct LiqState {
  int a = 0;
  int b = 0;
  int c = 0;
};

using LiqDist = std::vector<std::vector<std::vector<int>>>;

std::vector<LiqState> possible_states(LiqState state, LiqState max_value) {
  std::vector<LiqState> answer;

  answer.push_back(LiqState{max_value.a, state.b, state.c});
  answer.push_back(LiqState{state.a, max_value.b, state.c});
  answer.push_back(LiqState{state.a, state.b, max_value.c});

  answer.push_back(LiqState{0, state.b, state.c});
  answer.push_back(LiqState{state.a, 0, state.c});
  answer.push_back(LiqState{state.a, state.b, 0});

  int delta;

  delta = std::min(max_value.a - state.a, state.b);
  answer.push_back(LiqState{state.a + delta, state.b - delta, state.c});

  delta = std::min(max_value.a - state.a, state.c);
  answer.push_back(LiqState{state.a + delta, state.b, state.c - delta});

  delta = std::min(max_value.b - state.b, state.a);
  answer.push_back(LiqState{state.a - delta, state.b + delta, state.c});

  delta = std::min(max_value.b - state.b, state.c);
  answer.push_back(LiqState{state.a, state.b + delta, state.c - delta});

  delta = std::min(max_value.c - state.c, state.b);
  answer.push_back(LiqState{state.a, state.b - delta, state.c + delta});

  delta = std::min(max_value.c - state.c, state.a);
  answer.push_back(LiqState{state.a - delta, state.b, state.c + delta});

  return answer;
}

LiqDist bfs(LiqState start, LiqState max_value, int N) {
  std::queue<LiqState> states;
  states.push(start);

  LiqDist distances(N,
                    std::vector<std::vector<int>>(N, std::vector<int>(N, INT_MAX)));
  distances[start.a][start.b][start.c] = 0;

  while (!states.empty()) {
    LiqState now = states.front();
    states.pop();

    std::vector<LiqState> possible = possible_states(now, max_value);
    for (LiqState state : possible) {
        if (distances[state.a][state.b][state.c] == INT_MAX) {
            distances[state.a][state.b][state.c] = distances[now.a][now.b][now.c] + 1;
            states.push(state);
        }
    }
  }
  return distances;
}

int main() {
  LiqState max_value;
  std::cin >> max_value.a >> max_value.b >> max_value.c;

  int end;
  std::cin >> end;

  int N = 101;
  LiqDist distances = bfs(LiqState{0, 0, 0}, max_value, N);

  int answer = INT_MAX;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      answer = std::min(answer, distances[end][i][j]);
      if (i == 3) {
        answer = std::min(answer, distances[i][end][j]);
      }
      answer = std::min(answer, distances[i][end][j]);
      answer = std::min(answer, distances[i][j][end]);
    }
  }
  if (answer == INT_MAX) {
    std::cout << -1;
  } else {
    std::cout << answer;
  }
}