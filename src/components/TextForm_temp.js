import React, { useState } from 'react'


export default function TextForm(props) {
    const handleupClick = () => {
        // console.log("Uppercase was clicked " + text);
        let newText = text.toUpperCase();
        setText(newText)
        props.showAlert("Converted to Capital Case","success");
    }
    const handlelowClick = () => {
        // console.log("Uppercase was clicked " + text);
        let newText = text.toLowerCase();
        setText(newText)
        props.showAlert("Converted to Lower Case","success");
    }
    const handleclearClick = () => {
        // console.log("Uppercase was clicked " + text);
        setText("");
        props.showAlert("Text Cleared","success");
    }
    const handlecapClick = () => {
        let words = text.split(" ");
        let capitalizedWords = words.map((word) => {
            return word.charAt(0).toUpperCase() + word.slice(1).toLowerCase();
        });
        let newText = capitalizedWords.join(" ");
        setText(newText);
        props.showAlert("Text Capitalized","success");

    }

    const handleOnChange = (event) => {
        // console.log("OnChange");
        setText(event.target.value);
    }

    const handlecopyClick = (event) => {
        var text = document.getElementById("myBox");
        text.select();
        navigator.clipboard.writeText(text.value)
        props.showAlert("Copied to Clipboard","success");
    }


    const handleExtraClick = (event) => {
        let newText = text.split(/[  ]+/);
        setText(newText.join(" "))
        props.showAlert("Extra spaces Removed","success");
    }
    const [text, setText] = useState("");
    // text="new text"; //Wrong way to change state
    // setText("new text"); //Correct way to change to state
    return (
        <>
            <div className='container' style={{ color: props.mode === 'dark' ? 'white' : '#042743' }}>
                <h1>{props.heading}</h1>
                <div className="mb-3">
                    <textarea className="form-control" value={text} onChange={handleOnChange} style={{ backgroundColor: props.mode === 'dark' ? 'grey' : 'white', color: props.mode === 'dark' ? 'white' : '#042743' }} id="myBox" rows="12"></textarea>
                </div>
                <button className="btn btn-primary mx-2 " onClick={handleupClick}>Convert to Uppercase</button>
                <button className="btn btn-primary mx-2" onClick={handlelowClick}>Convert to Lowercase</button>
                <button className="btn btn-primary mx-2" onClick={handleclearClick}>Clear Text</button>
                <button className="btn btn-primary mx-2" onClick={handlecapClick}>Capatalize Text</button>
                <button className="btn btn-primary mx-2" onClick={handlecopyClick}>Copy Text</button>
                <button className="btn btn-primary mx-2" onClick={handleExtraClick}>Remove Extra Spaces</button>
            </div>
            <div className='container my-3' style={{ color: props.mode === 'dark' ? 'white' : '#042743' }}>
                <h1>Your Text Summary</h1>
                <p>{text.trim().length === 0 ? 0 : text.trim().split(/\s+/).length} words and {text.length} characters</p>
                <p>{0.008 * text.split(" ").length} Minutes to read </p>
                <h3>Preview</h3>
                <p>{text.trim().length === 0 ? 0 : text.trim().split(/\s+/).length} words</p>
            </div>
        </>
    )
}
