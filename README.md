Strength 

    1.Our model takes various variables into account to measure the maximum traffic volume so that it is reliable and robust for solving the problem.
    2.We improve the normal network flow model to minimum cost maximum flow model so that the simulated cooperating system can not only guarantee the maximum flow at a time but also cost least congestion extent.
    3.We considered both dynamic and static feature of the traffic network.
    4.We take both the micro and marco view on the influence of bringing self-driving car into the traffic system.

Weakness
    1. The distriubtion of traffic flow in a day is not accurately estimated.
    2. Some part of the model is specified for the situation of big Settatle.
    3. Assumption of the mechanism of self-driving car may not fit the real situation in the future since it can't be precisely estimated.

Summary:  

​     Since self-driving car is on it's way to change the life of human, we try to make assumptions on how will self-driving car improve the traffic state of big Seattle.

​     First, we look into the impact of self-driving car on traffic congestion in a micro way.  We take the car-following behavior, number of lanes and road length into account, and propose a urban traffic flow model to measure the capability of road to load traffic flow. We then optimize the road capability by distribute different numbers of lanes to self-driving car.

​    To explore how self-driving car might contributes to the development of traffic jam,  we build a Bayesian network to represent the dynamic process of congestion, we use the belief propagation algorithm to generate each road's weighted contribution factor to the whole traffic congestion system with or without the presence of self-driving car.  From the result we can see that different roads contribute to the traffic jam in great difference. 

​    Finally, based on the previous model, we propose a minimum cost and maximum flow model to simulate the intelligent cooperating navigation system of self-driving car. We choose the maximum traffic capacity of each road as the flow limit and the weighted contribution factor as the cost.  In this way we distribute the car flow in order to minimize the whole congestion condition while maximize the flow from source to destination. We apply the model to the map data of big Seattle while considering different proportion of self-driving car. We produce the result that only the percentage of self-driving car surpass 0.385 we can get a significant remission of traffic congestion. 



#### 1.Traffic Flow Model



##### 1.1 Traffic Flow

​    in this section we propose a traffic flow model to measure the burden of traffic,  we take the length of car, the speed of different vehicles lanes of roads together to measure how large the traffic flow is in the normal time and peak time.

​     math equations....

​     traffic flow evaluation 

​     road capacity evaluation 

​     congestion evaluation 

​     sensitivity analyze

​     Graphs shows the result 

##### 1.2 Interaction between self-Driving and non-self-driving cars

1. a table shows the difference between self-driving cars and non-self driving cars

2. V(d) Graphs

3. get the optimal result 

   ​

#### 2.Dynamic Congestion Propagation Model

##### 2.1 Bayesian network and belief propagation

##### 2.2 Simulate Result



#### 3.Cooperating Navigation Model

##### 3.1 Flow Network

##### 3.2 Source And Sink Analyze

##### 3.3 Minimum Cost Maxinum Flow

##### 3.4 Sensitivity Analyze