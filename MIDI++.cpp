// Updated Main.cpp with enhanced features
#include "MIDIManager.h"
#include "UIManager.h"
#include "AudioAnalyzer.h"
#include "MIDIFileHandler.h"

class MIDIPlusPlusApp {
public:
    MIDIPlusPlusApp() {
        // Initialize subsystems
        midiManager = std::make_unique<MIDIManager>();
        uiManager = std::make_unique<UIManager>();
        audioAnalyzer = std::make_unique<AudioAnalyzer>();
        fileHandler = std::make_unique<MIDIFileHandler>();
        
        // Setup callbacks
        midiManager->setNoteCallback([this](int note, int velocity) {
            activeNotes[note] = velocity;
            audioAnalyzer->processNote(note, velocity);
        });
    }

    void run() {
        while (!uiManager->shouldClose()) {
            // Update MIDI input
            midiManager->update();
            
            // Begin UI frame
            uiManager->beginFrame();
            
            // Show main window
            showMainWindow();
            
            // Show additional windows
            showPianoRoll();
            showSpectrumAnalyzer();
            showMIDIFileControls();
            
            // End UI frame
            uiManager->endFrame();
        }
    }

private:
    std::unique_ptr<MIDIManager> midiManager;
    std::unique_ptr<UIManager> uiManager;
    std::unique_ptr<AudioAnalyzer> audioAnalyzer;
    std::unique_ptr<MIDIFileHandler> fileHandler;
    std::map<int, int> activeNotes;
    
    void showMainWindow() {
        ImGui::Begin("MIDI Plus Plus");
        
        // Device selection
        if (ImGui::Button("Refresh Devices")) {
            midiManager->refreshDevices();
        }
        
        // Visualization options
        ImGui::Combo("Visualization", &visMode, "Piano Roll\0Spectrogram\0Waveform\0");
        
        // Show active notes
        ImGui::Text("Active Notes:");
        for (const auto& [note, velocity] : activeNotes) {
            ImGui::Text("%s: %d", midiManager->noteToString(note).c_str(), velocity);
        }
        
        ImGui::End();
    }
    
    void showPianoRoll() {
        // Enhanced piano roll visualization
    }
    
    void showSpectrumAnalyzer() {
        // Audio spectrum visualization
    }
    
    void showMIDIFileControls() {
        // MIDI file save/load interface
    }
};

int main() {
    MIDIPlusPlusApp app;
    app.run();
    return 0;
}
