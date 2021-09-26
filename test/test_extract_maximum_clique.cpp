// Copyright (c) 2021 Sota Tsuji
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php

#include <gtest/gtest.h>

#include "extract_maximum_clique.hpp"
#include "graph.hpp"

namespace {
using namespace extraction_of_maximum_clique;

const WeightedGraph
    T1 = {Vertices{1, 2}, Edges{{1, 2}}, ReciprocalWeights{{{1, 2}, 1}}},
    T2 = {Vertices{2, 3, 5}, Edges{{2, 3}, {2, 5}, {3, 5}},
          ReciprocalWeights{{{2, 3}, 1}, {{2, 5}, 1}, {{3, 5}, 1}}},
    T3 = {Vertices{2, 3, 5}, Edges{{2, 3}, {3, 5}},
          ReciprocalWeights{{{2, 3}, 1}, {{3, 5}, 1}}},
    T4 = {Vertices{2, 3, 5}, Edges{{2, 3}, {2, 5}, {3, 5}},
          ReciprocalWeights{{{2, 3}, 1}, {{2, 5}, 1}, {{3, 5}, 2}}},
    S1 = {Vertices{1, 2, 3, 4}, Edges{{1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}},
          ReciprocalWeights{
              {{1, 2}, 1}, {{1, 3}, 1}, {{1, 4}, 1}, {{2, 3}, 1}, {{3, 4}, 1}}},
    S2 = {Vertices{1, 2, 3, 4, 5, 6, 7, 8},
          Edges{{1, 2},
                {1, 3},
                {1, 4},
                {1, 5},
                {2, 3},
                {2, 4},
                {2, 5},
                {3, 4},
                {3, 5},
                {4, 5},
                {5, 6},
                {5, 7},
                {6, 7},
                {6, 8},
                {7, 8}},
          ReciprocalWeights{{{1, 2}, 1},
                            {{1, 3}, 1},
                            {{1, 4}, 1},
                            {{1, 5}, 1},
                            {{2, 3}, 1},
                            {{2, 4}, 1},
                            {{2, 5}, 1},
                            {{3, 4}, 1},
                            {{3, 5}, 1},
                            {{4, 5}, 1},
                            {{5, 6}, 1},
                            {{5, 7}, 1},
                            {{6, 7}, 1},
                            {{6, 8}, 1},
                            {{7, 8}, 1}}};
WeightedGraph S3;
bool init = []() {
    S3 = S2;
    S3.e.insert({1, 6});
    S3.rw[{1, 6}] = 2;
    return true;
}();

TEST(VerticesOperationTest, OperatorAdditionAssignmentVertex) {
    Vertices v = {2, 4, 5, 7, 8, 9};
    const Vertices v1 = {2, 3, 4, 5, 7, 8, 9}, v2 = {2, 3, 4, 5, 7, 8, 9, 11};
    v += 3;
    EXPECT_EQ(v1, v);
    v += 11;
    EXPECT_EQ(v2, v);
}

TEST(IsCompleteGraphTest, True) {
    EXPECT_TRUE(is_complete_graph(T1));
    EXPECT_TRUE(is_complete_graph(T2));
}

TEST(IsCompleteGraphTest, False) {
    EXPECT_FALSE(is_complete_graph(T3));
    EXPECT_FALSE(is_complete_graph(T4));
}

TEST(InitializeGraphTest, xxx) {
    const auto U1 = initialize_graph(S1);
    EXPECT_EQ(S1, U1);
    const auto U2 = initialize_graph(S2);
    EXPECT_EQ(S3, U2);
}

TEST(DeleteVertexTest, xxx) {
    const WeightedGraph V1 = {Vertices{1, 2, 3}, Edges{{1, 2}, {1, 3}, {2, 3}},
                              ReciprocalWeights{
                                  {{1, 2}, 1}, {{1, 3}, 1}, {{2, 3}, 1}}},
                        V2 = {Vertices{1, 2, 3, 4, 6, 7, 8},
                              Edges{{1, 2},
                                    {1, 3},
                                    {1, 4},
                                    {1, 6},
                                    {2, 3},
                                    {2, 4},
                                    {2, 7},
                                    {3, 4},
                                    {6, 7},
                                    {6, 8},
                                    {7, 8}},
                              ReciprocalWeights{{{1, 2}, 1},
                                                {{1, 3}, 1},
                                                {{1, 4}, 1},
                                                {{1, 6}, 2},
                                                {{2, 3}, 1},
                                                {{2, 4}, 1},
                                                {{2, 7}, 2},
                                                {{3, 4}, 1},
                                                {{6, 7}, 1},
                                                {{6, 8}, 1},
                                                {{7, 8}, 1}}};
    const auto U1 = delete_vertex(S1, 4);
    EXPECT_EQ(V1, U1);
    const auto U2 = delete_vertex(S3, 5);
    EXPECT_EQ(V2, U2);
}

TEST(ExtractMaximumCliqueTest, xxx) {
    const Graph G1 = {Vertices{}, Edges{}}, G2 = {Vertices{4, 5, 9}, Edges{}},
                G3 = {Vertices{1, 3}, Edges{{1, 3}}},
                G4 = {Vertices{1, 2, 3}, Edges{{1, 2}, {1, 3}, {2, 3}}},
                G5 = {Vertices{1, 2, 3, 4},
                      Edges{{1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}}},
                G6 = {Vertices{1, 2, 3, 4, 5, 6, 7, 8}, Edges{{1, 2},
                                                              {1, 3},
                                                              {1, 4},
                                                              {1, 5},
                                                              {2, 3},
                                                              {2, 4},
                                                              {2, 5},
                                                              {3, 4},
                                                              {3, 5},
                                                              {4, 5},
                                                              {5, 6},
                                                              {5, 7},
                                                              {6, 7},
                                                              {6, 8},
                                                              {7, 8}}};
    EXPECT_EQ(0, extract_maximum_clique(G1).size());
    EXPECT_EQ(1, extract_maximum_clique(G2).size());
    EXPECT_EQ(2, extract_maximum_clique(G3).size());
    EXPECT_EQ(3, extract_maximum_clique(G4).size());
    EXPECT_EQ(3, extract_maximum_clique(G5).size());
    EXPECT_EQ(5, extract_maximum_clique(G6).size());
}

TEST(BinarySearchItrTest, xxx) {
    const Vertices v = {2, 4, 5, 7, 8, 9};
    EXPECT_EQ(5, *binary_search_itr(v.cbegin(), v.cend(), 5));
    EXPECT_EQ(2, *binary_search_itr(v.cbegin(), v.cend(), 2));
}
}  // namespace
