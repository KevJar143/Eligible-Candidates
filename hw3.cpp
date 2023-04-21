#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

vector<int> recursiveBestApplicant(const vector<pair<float, float>>& applicants, int start, int end) {

    // Base Case
    if (start >= end) {
        return {};
    }

    if (end - start == 1) {
        return {start};
    }

    // Divides the problem into left and right subranges, finding best applicants recursively.
    int mid = (start + end) / 2;
    vector<int> leftBest = recursiveBestApplicant(applicants, start, mid);
    vector<int> rightBest = recursiveBestApplicant(applicants, mid, end);

    set<int> eligibleCandidates;

    // Inserts eligible candidates into the set.
    for (const auto& leftIndex : leftBest) {
        bool isBest = true;
        for (const auto& rightIndex : rightBest) {
            if (applicants[rightIndex].first > applicants[leftIndex].first &&
                applicants[rightIndex].second < applicants[leftIndex].second) {
                isBest = false;
                break;
            }
        }
        if (isBest) {
            eligibleCandidates.insert(leftIndex);
        }
    }

    // Compares rightBest and leftBest applicants, checks eligibility
    for (const auto& rightIndex : rightBest) {
        bool isBest = true;
        for (const auto& leftIndex : leftBest) {
            if (applicants[leftIndex].first > applicants[rightIndex].first &&
                applicants[leftIndex].second < applicants[rightIndex].second) {
                isBest = false;
                break;
            }
        }
        // inserts eligible candidates into the set,
        if (isBest) {
            eligibleCandidates.insert(rightIndex);
        }
    }

    return vector<int>(eligibleCandidates.begin(), eligibleCandidates.end());
}

vector<int> BestApplicants(const vector<pair<float, float>>& applicants) {
    return recursiveBestApplicant(applicants, 0, applicants.size());
}
