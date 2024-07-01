**TASK. Try adapter pattern one more time**
1. Port code base for adapters to make it work.

2. Propose one example where Adapter pattern can help with program design.

# Example 1
The example could be adaptation of data formats: CSV to JSON, for instance.

Example of real-case usage with the data-format adaptation is the following:
- Scenario: An external API returns responses in a format that differs from my internal data structures.
- Solution: Usage of an adapter to transform the API responses into the format required by application. For example, an API might return user data as a flat JSON object, while application expects a nested User object with address and contact details as separate fields.

So, when we have one class that receives API responses, and other program components that expect object as an input, we can use an adaptor to convert all the data needed.

# Example 2
### Real-World Example: Android's `RecyclerView.Adapter`

#### Scenario

In Android development, `RecyclerView` is a powerful and flexible component for displaying a large dataset of items in a scrollable list. The `RecyclerView.Adapter` acts as an adapter between the data source and the `RecyclerView`, handling the creation and binding of view holders to display the data.

#### Explanation

1. **Data Source**: You have a dataset, such as a list of objects (e.g., a list of contacts).

2. **View Holder**: A `RecyclerView.ViewHolder` class holds the view for each item in the dataset. This could include various UI components like `TextView`, `ImageView`, etc.

3. **RecyclerView.Adapter**: This adapter class binds the data from your dataset to the view holders. It translates the dataset into individual list items that the `RecyclerView` can display.
    - **onCreateViewHolder**: This method is called when the `RecyclerView` needs a new view holder. It inflates the item layout and creates the view holder.
    - **onBindViewHolder**: This method binds the data from the dataset to the view holder. It sets the values of the UI components in the view holder based on the data.
    - **getItemCount**: This method returns the total number of items in the dataset.

4. **Integration with RecyclerView**: The `RecyclerView.Adapter` is set on the `RecyclerView` to manage the data and create the necessary views.

### Key Components
- **RecyclerView**: The UI component that displays the list.
- **View Holder**: Encapsulates the view for each list item.
- **Adapter**: Bridges the data source and the `RecyclerView`, creating and binding view holders.

### Summary
The `RecyclerView.Adapter` in Android adapts the data source to the `RecyclerView`, allowing for efficient and flexible display of large datasets. The adapter manages the creation and binding of view holders, translating the data into views that the `RecyclerView` can display.
