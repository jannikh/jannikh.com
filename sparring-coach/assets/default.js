// // Remove the "Continuing previous chat" alert after 5 seconds - NOT WORKING
// setInterval(() => {
//   const targetElement = document.querySelector(
//     ".MuiStack-root > .dropzone.MuiBox-root > .MuiStack-root"
//   );
//   const alertMessageElement = document.querySelector(
//     ".MuiStack-root > .dropzone.MuiBox-root > .MuiStack-root > .MuiPaper-root > .MuiAlert-message"
//   );

//   if (targetElement && alertMessageElement) {
//     const alertMessageText = alertMessageElement.textContent.trim();
//     if (alertMessageText === "Continuing previous chat") {
//       setTimeout(() => {
//         targetElement.style.display = "none";
//       }, 5000);
//     } else {
//       targetElement.style.display = "block";
//     }
//   } else {
//     if (targetElement) {
//       targetElement.style.display = "block";
//     }
//   }
// }, 1000);
