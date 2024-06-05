**TASK. Object Pool**

Object pool pattern allows us to avoid frequent allocations for some class in case if we know the maximal count of objects that can exist at any moment of time.

As a part of this task you should create a class MegaData which contains 2 arrays:
* the first one with name smallArray should contain 1024 float numbers.
* the second one with name bigArray should contain 1024*1024 double numbers.
The default value for all of the elements should be 42.0 and we should have a reset method to get default state

Now you should implement the class MegaDataPool that should use pool size as an input for constructor. This class should have const std::vector<MegaData> which should be init with the size provided to consructor.
MegaDataPool should provide acquire and release method that allow client code to get one of that preallocated objects for temporary use and return it to the pool via release method. Some service methods like size(), usedSize can be added to API.

Write unit tests to ensure that pool works fine and handles different potential issues.
