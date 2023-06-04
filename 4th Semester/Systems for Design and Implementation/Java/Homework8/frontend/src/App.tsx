import React from 'react';
import RidesPage from "./RidesPage";

import { ThemeProvider, createTheme } from '@mui/material';
import {LocalizationProvider} from "@mui/x-date-pickers";
import {AdapterDateFns} from "@mui/x-date-pickers-pro/AdapterDateFns";

function App() {
  const theme = createTheme();
  return (
      <ThemeProvider theme={theme}>
          <LocalizationProvider dateAdapter={AdapterDateFns} >
            <RidesPage/>
          </LocalizationProvider>
      </ThemeProvider>
  );
}

export default App;
