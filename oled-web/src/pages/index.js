import React from 'react';
import PropTypes from 'prop-types';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogTitle from '@material-ui/core/DialogTitle';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogActions from '@material-ui/core/DialogActions';
import Typography from '@material-ui/core/Typography';
import { withStyles } from '@material-ui/core/styles';
import withRoot from '../withRoot';
import FormControl from '@material-ui/core/FormControl';
import TextField from '@material-ui/core/TextField';
import Radio from '@material-ui/core/Radio';
import RadioGroup from '@material-ui/core/RadioGroup';
import FormControlLabel from '@material-ui/core/FormControlLabel';

const styles = theme => ({
  root: {
    textAlign: 'center',
    paddingTop: theme.spacing.unit * 10,
  },
  formControl: {
    margin: theme.spacing.unit,
    textAlign: 'center',
    minWidth: 160,
  },
  selectEmpty: {
    marginTop: theme.spacing.unit * 2,
  },
});

class Index extends React.Component {
  state = {
    open: false,
    fontsize: 13,
    txtVal:' ',
    selectedValue: '0'
  };

  handleClose = () => {
    this.setState({
      open: false,
    });
  };

  handleClick = () => {
    this.setState({
      open: true,
    });
/*  fetch('http://afeifly.f3322.net:5000/sendmsg', {
    method: 'POST',
    headers: {
      'Accept': 'application/json',
      'content-type': 'application/json',
      'Authorization':'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE4NjQwMzAwNzgsImlzcyI6ImUwOGY2YWQyMzk3YzQ0YTc4YTIxMzYwZjhhMDJkZjdiIiwiaWF0IjoxNTQ4NjcwMDc4fQ.TfeI8Nk-82tqCWJvyQXlwMpTsOPolBTq1sVAXctfZzo',
    },
    body: JSON.stringify({
      entity_id: 'miio_acpartner.xmgw',
      message: 'hello',
    })
  })
*/
//  fetch("http://afeifly.f3322.net:5000/sendmsg", {
  fetch("/sendmsg", {
	    method:"POST"
	  , body:new URLSearchParams(
		  "msg="
		  + this.state.txtVal 
	  )
  })


  };

  handleChange = event => {
	this.setState({ selectedValue: event.target.value });  
  };
  handleTxtChange = event => {
	this.setState({ txtVal: event.target.value });  
  };


  render() {
    const { classes } = this.props;
    const { open } = this.state;
    return (
      <div className={classes.root}>
        <Dialog open={open} onClose={this.handleClose}>
          <DialogTitle>Hi</DialogTitle>
          <DialogContent>
            <DialogContentText>Be better.</DialogContentText>
            <DialogContentText>
		  {this.state.txtVal}
		  {this.state.selectedValue}
 	    </DialogContentText>
          </DialogContent>
          <DialogActions>
            <Button color="primary" onClick={this.handleClose}>
              OK
            </Button>
          </DialogActions>
        </Dialog>
        <Typography variant="h4" gutterBottom>
          Welcome home !
        </Typography>
	<form  autoComplete="off">
<FormControl component="fieldset" className={classes.formControl}>
	 <TextField
          id="standard-full-width"
	  onChange={this.handleTxtChange}
          label="Please"
          style={{ marginBottom: 5,width:400, }}
          margin="normal"
          placeholder="Input here"
          InputLabelProps={{
            shrink: true,
          }}
        />
        <Button variant="contained" color="secondary" onClick={this.handleClick}>
          Send
        </Button>
</FormControl>
	</form>
      </div>
    );
  }
}

Index.propTypes = {
  classes: PropTypes.object.isRequired,
};

export default withRoot(withStyles(styles)(Index));
