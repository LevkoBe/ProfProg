**TASK. Try adapter pattern one more time**
1. Port code base for adapters to make it work.

2. Propose one example where Adapter pattern can help with program design.

The example could be adaptation of data formats: CSV to JSON, for instance.

Example of real-case usage with the data-format adaptation is the following:
- Scenario: An external API returns responses in a format that differs from my internal data structures.
- Solution: Usage of an adapter to transform the API responses into the format required by application. For example, an API might return user data as a flat JSON object, while application expects a nested User object with address and contact details as separate fields.

So, when we have one class that receives API responses, and other program components that expect object as an input, we can use an adaptor to convert all the data needed.
