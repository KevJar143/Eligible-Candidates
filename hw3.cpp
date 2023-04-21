#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

vector<int> recursiveBestApplicant(const vector<pair<float, float>>& applicants, int start, int end) {
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

    // Compares leftBest and rightBest applicants
    for (const auto& leftIndex : leftBest) {
        bool isBest = true;
        for (const auto& rightIndex : rightBest) {
            float leftWPM = applicants[leftIndex].first;
            float leftIPM = applicants[leftIndex].second;
            float rightWPM = applicants[rightIndex].first;
            float rightIPM = applicants[rightIndex].second;

            if (rightWPM > leftWPM && rightIPM < leftIPM) {
                isBest = false;
                break;
            }
        }
        // Inserts eligible candidates into the set.
        if (isBest) {
            eligibleCandidates.insert(leftIndex);
        }
    }

    // Compares rightBest and leftBest applicants
    for (const auto& rightIndex : rightBest) {
        bool isBest = true;
        for (const auto& leftIndex : leftBest) {
            float leftWPM = applicants[leftIndex].first;
            float leftIPM = applicants[leftIndex].second;
            float rightWPM = applicants[rightIndex].first;
            float rightIPM = applicants[rightIndex].second;

            if (leftWPM > rightWPM && leftIPM < rightIPM) {
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
