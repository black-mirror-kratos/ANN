struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron;

typedef vec<Neuron> Layer;

// --------------- class Neuron --------------------------------
class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void setOutputVal(double val) { p_val = val; }
    double getOutputVal(void) const { return p_val; }
    void feedForward(const Layer &prevLayer);
    void calcOutGrads(double targetVal) { double delta = targetVal - p_val; p_grads = delta * Neuron::TFD(p_val); }
    void calcHiddenGrads(const Layer &nextLayer) { double dow = sumDOW(nextLayer); p_grads = dow * Neuron::TFD(p_val); }
    void updateInputWeights(Layer &prevLayer);

private:
    static double eta;  
    static double alpha;
    static double TF(double x) { return tanh(x); }
    static double TFD(double x){ return 1.0 - tanh(x) * tanh(x); }
    static double randomWeight(void) { return rand() / double(RAND_MAX); }
    double sumDOW(const Layer &nextLayer) const { double s=0.0; rep(i,nextLayer.size()-1) s+=p_connections[i].weight*nextLayer[i].p_grads; return s; }
    double p_val;
    vec<Connection> p_connections;
    unsigned p_myIndex;
    double p_grads;
};

double Neuron::eta = 0.15;    // overall net learning rate, [0.0..1.0]
double Neuron::alpha = 0.5;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
    rep(i,numOutputs) {
        p_connections.push_back(Connection());
        p_connections.back().weight = randomWeight();
    }
    p_myIndex = myIndex;
}

void Neuron::updateInputWeights(Layer &prevLayer)
{
    rep(i,prevLayer.size()) {
        Neuron &neuron = prevLayer[i];
        double oldDeltaWeight = neuron.p_connections[p_myIndex].deltaWeight;

        double newDeltaWeight =
                eta
                * neuron.getOutputVal()
                * p_grads
                + alpha
                * oldDeltaWeight;

        neuron.p_connections[p_myIndex].deltaWeight = newDeltaWeight;
        neuron.p_connections[p_myIndex].weight += newDeltaWeight;
    }
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;
    rep(i,prevLayer.size()) {
        sum += prevLayer[i].getOutputVal() *
                prevLayer[i].p_connections[p_myIndex].weight;
    }
    p_val = Neuron::TF(sum);
}

//------------------------------------------------------