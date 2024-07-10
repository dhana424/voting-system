#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Candidate class to store candidate information
class Candidate {
public:
    string name;
    int votes;

    Candidate(string n) : name(n), votes(0) {}

    bool operator<(const Candidate& other) const {
        // Sort candidates by number of votes (descending order)
        return votes > other.votes;
    }
};

// VotingSystem class to manage the voting process
class VotingSystem {
private:
    vector<Candidate> candidates;

public:
    // Add candidate to the system
    void addCandidate(const string& name) {
        candidates.push_back(Candidate(name));
    }

    // Vote for a candidate
    bool vote(const string& candidateName) {
        for (auto& candidate : candidates) {
            if (candidate.name == candidateName) {
                candidate.votes++;
                return true;
            }
        }
        return false; // Candidate not found
    }

    // Display voting results
    void displayResults() {
        // Sort candidates by votes (descending order)
        sort(candidates.begin(), candidates.end());

        cout << "\nVoting Results:\n";
        for (auto& candidate : candidates) {
            cout << candidate.name << ": " << candidate.votes << " votes\n";
        }

        // Check for ties
        int maxVotes = candidates[0].votes;
        vector<string> winners;
        winners.push_back(candidates[0].name);

        for (size_t i = 1; i < candidates.size(); ++i) {
            if (candidates[i].votes == maxVotes) {
                winners.push_back(candidates[i].name);
            } else {
                break; // Since candidates are sorted, no more ties possible
            }
        }

        if (winners.size() == 1) {
            cout << "\nThe winner is: " << winners[0] << " with " << maxVotes << " votes!\n";
        } else {
            cout << "\nThere is a tie between the following candidates:\n";
            for (const auto& winner : winners) {
                cout << winner << endl;
            }
            cout << "Each has " << maxVotes << " votes.\n";
        }
    }
};

int main() {
    VotingSystem votingSystem;
    int numCandidates, numVoters;
    string candidateName, voterChoice;

    cout << "Enter the number of candidates: ";
    cin >> numCandidates;

    // Input candidate names
    for (int i = 0; i < numCandidates; ++i) {
        cout << "Enter name of candidate " << i + 1 << ": ";
        cin >> candidateName;
        votingSystem.addCandidate(candidateName);
    }

    // Input number of voters
    cout << "Enter the number of voters: ";
    cin >> numVoters;

    // Voting process
    for (int i = 0; i < numVoters; ++i) {
        cout << "Voter " << i + 1 << ", enter your vote: ";
        cin >> voterChoice;

        // Validate and process the vote
        if (!votingSystem.vote(voterChoice)) {
            cout << "Invalid candidate. Please enter a valid candidate name.\n";
            i--; // Decrement i to allow the same voter to vote again
        } else {
            cout << "Thank you for your vote!\n";
        }
    }

    // Display results
    votingSystem.displayResults();

    return 0;
}