#include <stack>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define STICKS 3

int main(int argc, const char *argv[]) {
    stack<int> s[STICKS];
    stack< pair<int,int> > se, sb;
    
    int tt = 3;
    cout << "total: ";
    cin >> tt;
    for (int i=tt; i>0; --i) {
        s[0].push(i);
    }

    cout << "running " << s[0].size() << " hanota!" << endl;

    int total = s[0].size();
    int total_step = 0;
    while ( s[1].size() < total && s[2].size() < total ) {
        int got_move = 0;
        for ( int i=0; i<STICKS; ++i ) {
            while ( s[i].size() > 0 ) {
                //cout << "s" << i << " size: " << s[i].size() << endl;
                map<int, int> value;
                for ( int j=(i+1)%STICKS; s[i].size()>0 && j!=i; j=(j+1)%STICKS ) {
                    if ( sb.size() > 0 && i == sb.top().first && j == sb.top().second ) {
                        sb.pop();
                        value[j] = -1;
                        continue;
                    }
                    if ( s[j].size() == 0 || s[j].top() > s[i].top() ) {
                        //if ( se.size() > 0 && (se.top().first == j && se.top().second == i) ) {
                        if ( se.size() > 0 && se.top().second == i ) {
                            value[j] = -1;
                            continue;
                        }
                        
                        int score = j;
                        if ( s[j].size() == 0 ) {
                            score = j;
                        }
                        value[j] = score;
                        if ( s[j].size() > 0 ) {
                            //value[j] += s[j].top();
                        }
                    } else {
                        value[j] = -1;
                    }
                }

                // value the score
                int dest = -1, max = -1;
                for ( map<int,int>::const_iterator cit=value.begin(); cit != value.end(); ++cit ) {
                    if ( cit->second > max ) {
                        dest = cit->first;
                        max = cit->second;
                    }
                }

                if ( dest >= 0 ) {
                    int item = s[i].top();
                    s[dest].push(item);
                    s[i].pop();
                    pair<int,int> e;
                    e.first = i;
                    e.second = dest;
                    se.push(e);
                    cout << "move "<< item << " from s"<< i << " to s" << dest << " " << s[i].size() << endl;
                    got_move = 1;
                    total_step++;
                } else {
                    //cout << "no way to move on s" << i << endl;
                    break;
                }
            }
        }

        // back trace ... 
        if ( got_move == 0 && se.size() > 0 ) {
            pair<int, int> e = se.top();
            se.pop();
            int f = e.second, t = e.first;
            int item = s[f].top();
            s[f].pop();
            s[t].push(item);
            sb.push(pair<int, int>(t, f));
            cout << "back " << item << " from s" << f << " to s" << t << endl; 
        } else if ( got_move == 0 && se.size() == 0 ) {
            cout << "no way to backtrace ... " << endl;
            break;
        }
    }

    cout << "total move: " << total_step << endl;
}
