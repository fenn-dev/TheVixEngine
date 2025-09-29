namespace VIX
{
    namespace Internal
    {
        
    }

    class TheVIXEngine
    {
    public:
        TheVIXEngine();
        ~TheVIXEngine();

        void Initialize();
        void Shutdown();

        void Update(float deltaTime);
        void Render();
    private:
        
    };
} // namespace VIX
