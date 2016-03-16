#include "Neuron.h"

// ------------------ class Net -------------------
class Net
{
public:
    Net(const vec<unsigned> &topology);
    void feedForward(const vec<double> &inputVals);
    void backProp(const vec<double> &targetVals);
    void getResults(vec<double> &resultVals) const;

private:
    vec<Layer> p_layers;
    double p_error;
};

Net::Net(const vec<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    rep(i,numLayers) {
        p_layers.push_back(Layer());
        unsigned numOutputs = i == topology.size() - 1 ? 0 : topology[i + 1];
        reep(j,0,topology[i]) {
            p_layers.back().push_back(Neuron(numOutputs, j));
            cout << "Made a Neuron!" << endl;
        }
        p_layers.back().back().setOutputVal(1.0);
    }
}

void Net::getResults(vec<double> &resultVals) const
{
    resultVals.clear();

    rep(i,p_layers.back().size() - 1) {
        resultVals.push_back(p_layers.back()[i].getOutputVal());
    }
}

void Net::feedForward(const vec<double> &inputVals)
{
    assert(inputVals.size() == p_layers[0].size() - 1);
    rep(i,inputVals.size()) {
        p_layers[0][i].setOutputVal(inputVals[i]);
    }
    reep(i,1,p_layers.size()-1) {
        Layer &prevLayer = p_layers[i - 1];
        for (unsigned n = 0; n < p_layers[i].size() - 1; ++n) {
            p_layers[i][n].feedForward(prevLayer);
        }
    }
}

void Net::backProp(const vec<double> &targetVals)
{
    // Calculate overall net error (RMS of output neuron errors)

    Layer &outputLayer = p_layers.back();
    p_error = 0.0;

    rep(i,outputLayer.size() - 1) {
        double delta = targetVals[i] - outputLayer[i].getOutputVal();
        p_error += delta * delta;
    }
    p_error /= outputLayer.size() - 1; // get average error squared
    p_error = sqrt(p_error); // RMS

    // Calculate output layer gradients

    rep(i,outputLayer.size() - 1) {
        outputLayer[i].calcOutGrads(targetVals[i]);
    }

    // Calculate hidden layer gradients

    peer(i,p_layers.size() - 2,1) {
        Layer &hiddenLayer = p_layers[i];
        Layer &nextLayer = p_layers[i + 1];

        rep(j,hiddenLayer.size()) {
            hiddenLayer[j].calcHiddenGrads(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer, update connection weights

    peer(i,p_layers.size() - 1,1) {
        Layer &layer = p_layers[i];
        Layer &prevLayer = p_layers[i - 1];
        rep(j,layer.size() - 1) {
            layer[j].updateInputWeights(prevLayer);
        }
    }
}

//--------------------------------------------------